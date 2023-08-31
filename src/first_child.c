/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 18:40:35 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(t_data data, int *fd_pipe, char **env)
{
	int	fd_in;

	// 1) close extrem of pipe not used
	close(fd_pipe[0]);

	// 2) open() file from which read
	fd_in = open(data.in_file, O_RDONLY); // modify options/mods
	if (fd_in == -1)
		return (perror(data.shell), errno);

	// 3) redirect the input and the output
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (perror(data.shell), errno);
	if (dup2(fd_pipe[1], STDOUT_FILENO) == -1) // remove this to verify if the cmd1 works
		return (perror(data.shell), errno);

	// 4) execute the program
	if (execve(data.cmd1[0], data.cmd1, env) == -1)
		return (perror(data.shell), errno);
	return (0);
}

