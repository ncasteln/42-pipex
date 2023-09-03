/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 21:45:46 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	create_pipes(t_pipe *data)
{
	int	i;

	data->pipe_end = malloc(sizeof(int *) * (data->n_cmd - 1));
	if (!data->pipe_end)
		exit_error(data, "malloc()", errno);
	i = 0;
	while (i < (data->n_cmd - 1))
	{
		data->pipe_end[i][0] = -1;
		data->pipe_end[i][1] = -1;
		i++;
	}
	i = 0;
	while (i < (data->n_cmd - 1))
	{
		if (pipe(data->pipe_end[i]) == -1)
			exit_error(data, "pipe()", errno);
		i++;
	}
}

static void	parse_data(t_pipe *data, int argc, char **argv, char **env)
{
	int i = 0;

	// PATH & CMDS
	data->n_cmd = argc - 3;
	data->path = get_env_path(env);
	data->cmd = parse_all_cmd(data, argv);

	// PID COLLECTION
	data->ps_id = malloc(sizeof(pid_t) * data->n_cmd);
	if (!data->ps_id)
		exit_error(data, "malloc()", errno);

	// PIPES COLLECTION
	create_pipes(data);

	// IN AND OUTFILES
	data->infile = argv[1];
	data->outfile = argv[argc - 1];

	// HERE_DOC
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		data->here_doc = 1;
}

static void	init_data(t_pipe *data)
{
	data->ps_id = NULL;
	data->pipe_end = NULL;
	data->path = NULL;
	data->n_cmd = 0;
	data->cmd = NULL;
	data->infile = NULL;
	data->outfile = NULL;
	data->here_doc = 0;
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	data;
	int		i; // index of current process

	if (argc < 5)
		exit_error(NULL, "argc", INV_ARG);
	init_data(&data);
	parse_data(&data, argc, argv, env);
	i = 0;
	while (i < data.n_cmd)
	{
		data.ps_id[i] = fork();
		if (data.ps_id[i] == -1)
			exit_error(&data, "fork()", errno);
		else if (data.ps_id[i] == 0) // children processes
		{
			if (i == 0)
				first_child(&data, 0, env);
			else if (i == data.n_cmd - 1)
				last_child(&data, i, env);
			else
				mid_child(&data, i, env);
		}
		else // parent
			i++;
	}
	return (parent(&data));
}
