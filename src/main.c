/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 11:19:34 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	free_data(t_data *data)
{
	if (data->ps_id)
		free(data->ps_id);
	if (data->path)
		free_dptr(data->path);
	if (data->cmd1)
		free_dptr(data->cmd1);
	if (data->cmd2)
		free_dptr(data->cmd2);
}

static void	parse_data(t_data *data, char **argv, char **env)
{
	data->ps_id = malloc(sizeof(pid_t) * 2);
	if (!data->ps_id)
		exit_error(data, "malloc()", errno);
	data->path = get_env_path(env);
	data->cmd1 = find_cmd(argv[2], data->path);
	data->cmd2 = find_cmd(argv[3], data->path);
	data->infile = argv[1];
	data->outfile = argv[4];
	if (!(data->cmd1) || !(data->cmd2))
		exit_error(data, "argv", INV_ARG);
}

static void	init_data(t_data *data)
{
	data->ps_id = NULL;
	data->path = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->infile = NULL;
	data->outfile = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
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
