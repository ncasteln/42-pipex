/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 09:29:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_pipe *data, int i, char **env)
{
	if (dup2(data->pipe_end[i - 1][0], STDIN_FILENO) == 1)
		exit_error(data, "dup2()", errno);
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	close_fds(data);
	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
