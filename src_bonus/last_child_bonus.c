/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/05 12:01:11 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_pipe *data, int i, char **env)
{
	// print_pipe_end(data);
	// if pipeline
	// if (data->n_cmd > 2)
	// {
	// 	int	j;
	// 	j = data->n_cmd - 1;
	// 	while (j >= 0)
	// 	{
	// 		if (j == (i - 1))
	// 		{
	// 			// close only write
	// 			close(data->pipe_end[j][1]);
	// 		}
	// 		else if (j != i)
	// 		{
	// 			close(data->pipe_end[j][0]);
	// 			close(data->pipe_end[j][1]);
	// 		}
	// 		j--;
	// 	}
	// }
	// close(data->pipe_end[i - 1][1]);


	// // i read from
	if (dup2(data->pipe_end[i - 1][0], STDIN_FILENO) == 1)
		exit_error(data, "dup2()", errno);
	// i write to
	if (dup2(data->fd_outfile, STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);

	// close unnecessary things
	if (data->n_cmd > 2)
	{
		int	j;
		j = data->n_cmd - 3;
		while (j >= 0)
		{
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
			j--;
		}
	}
	close(data->pipe_end[i - 1][0]);
	close(data->pipe_end[i - 1][1]);
	close(data->fd_outfile);
	close(data->fd_infile);

	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
