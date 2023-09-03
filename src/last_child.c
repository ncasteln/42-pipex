/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 18:49:18 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_child(t_pipe *data, int *pipe_end, char **env)
{
	int	fd_outfile;

	if (close(pipe_end[1]))
		exit_error(data, "close()", errno);
	fd_outfile = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		exit_error(data, data->outfile, errno);
	if (dup2(pipe_end[0], STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (close(pipe_end[0]))
		exit_error(data, "close()", errno);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (close(fd_outfile))
		exit_error(data, "close()", errno);
	if (execve(data->cmd2[0], data->cmd2, env) == -1)
		exit_error(data, data->cmd2[0], CMD_NOT_FOUND);
}
