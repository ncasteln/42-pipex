/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/05 12:00:54 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* int i is the index of the process necessary to remember which pipe close */
void	first_child(t_pipe *data, int i, char **env)
{
	if (data->here_doc)
	{
		// if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		// 	exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
		exit(1);
	}

	// NO HERE_DOC
	if (data->fd_infile == -1)
		exit_error(data, data->infile, errno);
	// i read from
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	// i write to
	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);

	// i close unnecessary fd
	if (data->n_cmd > 2)
	{
		int	j;
		j = data->n_cmd - 2;
		while (j > 0)
		{
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
			j--;
		}
	}
	close(data->fd_infile);
	close(data->fd_outfile);
	close(data->pipe_end[i][0]);
	close(data->pipe_end[i][1]);

	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
