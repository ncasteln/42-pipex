/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 16:41:38 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	free_dptr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void	free_data(t_pipe *data)
{
	// if (data->ps_id)
	// 	free(data->ps_id);
	// if (data->path)
	// 	free_dptr(data->path);
	// if (data->cmd1)
	// 	free_dptr(data->cmd1);
	// if (data->cmd2)
	// 	free_dptr(data->cmd2);
}

static void print_cmd(char ***cmd) //remove
{
	int	i, j;

	i = 0;
	ft_printf("_COMMANDS STORED_\n");
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			ft_printf("[%s]", cmd[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

static void print_pid(int *p, int n_cmd) //remove
{
	int	i;

	i = 0;
	ft_printf("_PS_ID_\n");
	while (i < n_cmd)
	{
		ft_printf("[%d]\n", p[i]);
		i++;
	}
}

static void	parse_data(t_pipe *data, int argc, char **argv, char **env)
{
	// PATH & CMDS
	data->n_cmd = argc - 3;
	data->path = get_env_path(env);
	data->cmd = parse_all_cmd(data, argv);
	print_cmd(data->cmd); // --------------------------------------------- remove

	// PID COLLECTION
	data->ps_id = malloc(sizeof(pid_t) * data->n_cmd);
	if (!data->ps_id)
		exit_error(data, "malloc()", errno);

	// PIPES COLLECTION
	data->pipe_end = malloc(sizeof(int *) * (data->n_cmd - 1));
	if (!data->pipe_end)
		exit_error(data, "malloc()", errno);
	data->pipe_end[0] = malloc(sizeof(int) * 2);
	data->pipe_end[1] = malloc(sizeof(int) * 2);


	ft_printf("The cmds are %d.\n", data->n_cmd);
	ft_printf("I created space for %d pipes.\n", data->n_cmd - 1);
	int i = 0;
	while (i < (data->n_cmd - 1))
	{
		data->pipe_end[i][0] = -1;
		data->pipe_end[i][1] = -1;
		i++;
	}
	ft_printf("pipe_end[0][0] = %d\n", data->pipe_end[0][0]);
	ft_printf("pipe_end[0][1] = %d\n", data->pipe_end[0][1]);

	// IN AND OUTFILES
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
}

static void	init_pipe(t_pipe *data)
{
	data->ps_id = NULL;
	data->pipe_end = NULL;
	data->path = NULL;
	data->n_cmd = 0;
	data->cmd = NULL;
	data->infile = NULL;
	data->outfile = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	data;

	if (argc < 5)
		exit_error(NULL, "argc", INV_ARG);
	init_pipe(&data);
	parse_data(&data, argc, argv, env);



	int	i;

	i = 0;
	while (i < data.n_cmd)
	{
		if (pipe(data.pipe_end[i]) == -1)
			exit_error(&data, "pipe()", errno);
		data.ps_id[i] = fork();
		if (data.ps_id[i] == -1)
			exit_error(&data, "fork()", errno);
		else if (data.ps_id[i] == 0) // child process
		{
			// this code executed only for the CHILDREN
			if (i == 0) // first child
			{
				ft_printf("[FIRST]\n");
				ft_printf("[%s]\n", data.cmd[i][0]);
			}
			else if (i == data.n_cmd - 1) // last child
			{
				ft_printf("[LAST]\n");
				ft_printf("[%s]\n", data.cmd[i][0]);
			}
			else // mid child
			{
				ft_printf("[MID]\n");
				ft_printf("[%s]\n", data.cmd[i][0]);
			}

			char *args[] = {"echo", "Hello!", NULL};
			if (execve("Hi Bocals", args, NULL) == -1)
				exit(1);
		}
		else // parent
			i++;
	}
	print_pid(data.ps_id, data.n_cmd);

	// if (pipe(pipe_end) == -1)
	// 	exit_error(&data, "pipe()", errno);
	// data.ps_id[0] = fork();
	// if (data.ps_id[0] == -1)
	// 	exit_error(&data, "fork()", errno);
	// else if (data.ps_id[0] == 0)
	// 	first_child(&data, pipe_end, env);
	// else
	// {
	// 	data.ps_id[1] = fork();
	// 	if (data.ps_id[1] == -1)
	// 		error("fork()", errno);
	// 	if (data.ps_id[1] == 0)
	// 		last_child(&data, pipe_end, env);
	// 	else
	// 		return (parent(&data, pipe_end));
	// }
	return (0);
}
