/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/04 12:47:07 by ncasteln         ###   ########.fr       */
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
	// HERE DOC & EOF
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		data->here_doc = -1;
	if (data->here_doc)
	{
		if (argc < 6)
			exit_error(data, "argc", INV_ARG); // not enough argc for here_doc
		data->eof = argv[2];
	}

	// N_CMDS
	if (data->here_doc)
		data->n_cmd = argc - 4;
	else
		data->n_cmd = argc - 3;

	// PATH & CMDS
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
	data->eof = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	data;
	int		i; // index of current process

	if (argc < 5)
		exit_error(NULL, "argc", INV_ARG);
	init_data(&data);
	parse_data(&data, argc, argv, env);
	if (data.here_doc)
		data.here_doc = get_here_doc(&data);
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
