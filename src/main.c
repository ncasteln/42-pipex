/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/02 18:53:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void print_dptr(char **dptr) // remove
{
	int	i;

	i = 0;
	while (dptr[i])
	{
		ft_printf("[%s]\n", dptr[i]);
		i++;
	}
}

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

static void	free_data(t_data *data)
{
	if (data->path)
		free_dptr(data->path);
	if (data->cmd1)
		free_dptr(data->cmd1);
	if (data->cmd2)
		free_dptr(data->cmd2);
}

static void	parse_data(t_data *data, char **argv, char **env)
{
	data->path = get_env_path(env); // malloc()
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
		return (error("argc", INV_ARG), 107);
	init_data(&data);
	parse_data(&data, argv, env);
	if (!data.cmd1 || !data.cmd2)
		return (free_data(&data), error("argv", INV_ARG), 107);

	if (pipe(pipe_end) == -1) // -------------------------------------------- pipe()
		return (error("pipe()", errno), errno);
	id_1 = fork();  // ------------------------------------------------ first fork()
	if (id_1 == -1)
		return (error("fork()", errno), errno);
	else if (id_1 == 0)
		return (first_child(data, pipe_end, env));
	else
	{
		id_2 = fork(); // -------------------------------------------- second fork()
		if (id_2 == -1)
		{
			error("fork()", errno);
			return (parent(id_1, id_2, pipe_end));
		}
		if (id_2 == 0)
			return (last_child(data, pipe_end, env));
		else
			return (parent(id_1, id_2, pipe_end));
	}
	return (0);
}
