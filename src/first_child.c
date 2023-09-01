/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 16:47:31 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data data, int *pipe_end, char **env)
{
	int	fd_infile;

	if (close(pipe_end[0]) == -1)
		return (error("close()", errno));

	fd_infile = open(data.infile, O_RDONLY); // modify options/mods
	if (fd_infile == -1)
		return (error(data.infile, errno));
	if (dup2(fd_infile, STDIN_FILENO) == -1) // from now, 0 points to "infile" and not to "keyboard" anymore
		return (error("dup2()", errno));
	if (close(fd_infile) == -1)
		return (error("close()", errno));

	if (dup2(pipe_end[1], STDOUT_FILENO) == -1) // remove this to verify if the cmd1 works
		return (error("dup2()", errno));
	if (close(pipe_end[1]) == -1)
		return (error("close()", errno));

	execve(data.cmd1[0], data.cmd1, env);
	return (error(data.cmd1[0], CMD_NOT_FOUND));
}

