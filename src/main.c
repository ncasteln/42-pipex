/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 17:37:21 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	parse_data(t_data *data, char **argv, char **env)
{
	data->path = get_path(env);
	data->cmd1 = find_cmd(argv[2], data->path);
	data->cmd2 = find_cmd(argv[3], data->path);
	data->infile = argv[1];
	data->outfile = argv[4];
}

static void	init_data(t_data *data)
{
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
	pid_t	id_1;
	pid_t	id_2;

	if (argc < 5)
		return (1);
	init_data(&data);
	parse_data(&data, argv, env);
	if (pipe(pipe_end) == -1) // -------------------------------------------- pipe()
		return (error("pipe()", errno), errno);
	id_1 = fork();  // ------------------------------------------------ first fork()
	if (id_1 == -1)
		return (error("fork()", errno), errno);
	else if (id_1 == 0)
		first_child(data, pipe_end, env);
	else
	{
		id_2 = fork(); // -------------------------------------------- second fork()
		if (id_2 == -1)
		{
			//wait first child and return ?
		}
		if (id_2 == 0)
			last_child(data, pipe_end, env);
		else
			return (parent(data, id_1, id_2, pipe_end));
	}
	return (0);
}
