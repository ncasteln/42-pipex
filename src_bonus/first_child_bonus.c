/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 10:45:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* (i) is always the index of the current process, useful to differentiate
it from the others and redirect in/out accordingly */
static void	close_all(t_pipe *data, int i)
{
	int	j;

	j = data->n_cmd - 2;
	if (data->n_cmd > 2)
	{
		while (j > 0)
		{
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
			j--;
		}
	}
	close(data->pipe_end[i][0]);
	close(data->pipe_end[i][1]);
	close(data->fd_infile);
	close(data->fd_outfile);
}

void	first_child(t_pipe *data, int i, char **env)
{
	if (data->fd_infile == -1)
		exit(errno);
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	close_all(data, i); // ------------------------------ should protect ??????
	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
