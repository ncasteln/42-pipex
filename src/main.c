/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 13:53:53 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse_data(t_pipe *data, char **argv, char **env)
{
	if (!env || !env[0])
		exit_error(data, "env", INV_ENV);
	data->ps_id = malloc(sizeof(pid_t) * 2);
	if (!data->ps_id)
		exit_error(data, "malloc()", errno);
	data->path = get_env_path(env);
	data->cmd1 = parse_cmd(argv[2], data->path);
	data->cmd2 = parse_cmd(argv[3], data->path);
	if (!(data->cmd1) || !(data->cmd2))
		exit_error(data, "argv", INV_ARG);
	data->infile = argv[1];
	data->outfile = argv[4];
}

int	main(int argc, char **argv, char **env)
{
	t_pipe	data;
	int		pipe_end[2];

	if (argc != 5)
		exit_error(NULL, "argc", INV_ARG);
	init_data(&data);
	parse_data(&data, argv, env);
	if (pipe(pipe_end) == -1)
		exit_error(&data, "pipe()", errno);
	data.ps_id[0] = fork();
	if (data.ps_id[0] == -1)
		exit_error(&data, "fork()", errno);
	else if (data.ps_id[0] == 0)
		first_child(&data, pipe_end, env);
	else
	{
		data.ps_id[1] = fork();
		if (data.ps_id[1] == -1)
			error("fork()", errno);
		if (data.ps_id[1] == 0)
			last_child(&data, pipe_end, env);
		else
			return (parent(&data, pipe_end));
	}
	return (0);
}
