/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 18:09:57 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(t_data data, int *pipe_end, char **env)
{
	int	fd_infile;

	if (close(pipe_end[0]) == -1)
		return (error("close()", errno), errno);

	fd_infile = open(data.infile, O_RDONLY); // modify options/mods
	if (fd_infile == -1)
		return (error(data.infile, errno), errno);
	if (dup2(fd_infile, STDIN_FILENO) == -1) // from now, 0 points to "infile" and not to "keyboard" anymore
		return (error("dup2()", errno), errno);
	if (close(fd_infile) == -1)
		return (error("close()", errno), errno);

	if (dup2(pipe_end[1], STDOUT_FILENO) == -1) // remove this to verify if the cmd1 works
		return (error("dup2()", errno), errno);
	if (close(pipe_end[1]) == -1)
		return (error("close()", errno), errno);

	if (execve(data.cmd1[0], data.cmd1, env) == -1)
		return (error(data.cmd1[0], CMD_NOT_FOUND), 127);
	return (0);
}

