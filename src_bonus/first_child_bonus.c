/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 14:47:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
	(i) is always the index of the current process, useful to differentiate
	it from the others and redirect in/out accordingly.
*/

void	first_child(t_pipe *data, int i, char **env)
{
	if (data->fd_infile == -1)
		exit(errno);
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	close_fds(data);
	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
