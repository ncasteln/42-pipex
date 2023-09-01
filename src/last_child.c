/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 18:11:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	last_child(t_data data, int *pipe_end, char **env)
{
	int	outfile;

	close(pipe_end[1]);

	outfile = open(data.outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		return (error(data.outfile, errno), errno);

	if (dup2(pipe_end[0], STDIN_FILENO) == -1) // from now, 0 points to "pipe_end[0]" and not to "keyboard" anymore
		return (error("dup2()", errno), errno);
	close(pipe_end[0]);

	if (dup2(outfile, STDOUT_FILENO) == -1) // from now, 1 points to "outfile" and not to "terminal" anymore
		return (error("dup2()", errno), errno);
	close(outfile);

	if (execve(data.cmd2[0], data.cmd2, env) == -1)
		return (error(data.cmd1[0], CMD_NOT_FOUND), 127);
	return (0);
}
