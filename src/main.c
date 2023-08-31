/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 18:50:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void print_cmds(t_data data) // remove
{
	ft_printf("[cmd1]: ");
	int i = 0;
	while (data.cmd1[i])
	{
		ft_printf("[%s]", data.cmd1[i]);
		i++;
	}
	ft_printf("\n[cmd2]: ");
	i = 0;
	while (data.cmd2[i])
	{
		ft_printf("[%s]", data.cmd2[i]);
		i++;
	}
}

static void	init_data(t_data *data)
{
	data->shell = NULL;
	data->path = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->in_file = NULL;
	data->out_file = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		fd_pipe[2];
	pid_t	id_1;

	if (argc < 5)
		return (1);
	init_data(&data);
	data.shell = get_shell(env);
	data.path = get_path(env);
	data.cmd1 = find_cmd(argv[2], data.path);
	data.cmd2 = find_cmd(argv[3], data.path);
	data.in_file = argv[1];
	data.out_file = argv[4];
	// print_cmds(data); // remove

	if (pipe(fd_pipe) == -1)
		return (perror(data.shell), errno);
	id_1 = fork();
	if (id_1 == -1)
		return (perror(data.shell), errno);
	if (id_1 == 0)
		first_child(data, fd_pipe, env);
	else
	{
		pid_t	id_2;
		int		fd_out;

		id_2 = fork();
		if (id_2 == -1)
		{
			// parent needs to wait() for the first_child
		}
		if (id_2 == 0) // last_child()
		{
			close(fd_pipe[1]);
			fd_out = open(data.out_file, O_WRONLY);
			dup2(fd_pipe[0], STDIN_FILENO);
			dup2(fd_out, STDOUT_FILENO);
			execve(data.cmd2[0], data.cmd2, env);
		}
		else // parent()
		{
			// parent needs to waitpid() for both the processes
		}
	}
	return (0);
}





// int	main(int argc, char **argv, char **env)
// {
// 	t_data	data;

// 	if (argc < 5)
// 		return (1);
// 	init_data(&data);
// 	data.path = get_path(env);
// 	data.cmd1 = ft_split(argv[2], ' ');
// 	data.cmd2 = ft_split(argv[3], ' ');
// 	find_cmd(data.cmd1[0], data.path);
// 	find_cmd(data.cmd2[0], data.path);

// 	ft_printf("[cmd1]: ");
// 	ft_printf("[%s] [%s]\n", data.cmd1[0], data.cmd1[1]);
// 	ft_printf("[cmd2]: ");
// 	ft_printf("[%s] [%s]\n", data.cmd2[0], data.cmd2[1]);

// 	return (0);
// }
