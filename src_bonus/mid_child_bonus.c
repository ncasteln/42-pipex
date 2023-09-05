/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_child_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:38:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/05 12:01:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	mid_child(t_pipe *data, int i, char **env)
{
	// sleep(i + i);
	int	j;
	j = data->n_cmd - 2;
	while (j >= 0) // changed!!
	{
		if (j != i)
		{
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
		}
		else
			j--;
		j--;
	}

	if (dup2(data->pipe_end[i - 1][0], STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);

	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);

	close(data->fd_infile);
	close(data->fd_outfile);
	close(data->pipe_end[i - 1][0]);
	close(data->pipe_end[i - 1][1]);
	close(data->pipe_end[i][0]);
	close(data->pipe_end[i][1]);


	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
