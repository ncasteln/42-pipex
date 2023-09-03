/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_child_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:38:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 21:21:31 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	mid_child(t_pipe *data, int i, char **env)
{
	// sleep(i + i); // just to wait
	// ft_printf("\n[MID]\n");
	// ft_printf("[%s]\n", data->cmd[i][0]);

	// ft_printf("I close() fd that I don't need:\n");
	int	j;
	j = data->n_cmd - 1;
	while (j >= 0) // changed!!
	{
		if (j == (i - 1))
		{
			// close only write
			close(data->pipe_end[j][1]);
		}
		else if (j != i)
		{
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
		}
		j--;
	}


	// ft_printf("I read from fd[%d]\n", data->pipe_end[i - 1][0]);
	if (dup2(data->pipe_end[i - 1][0], STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);

	close(data->pipe_end[i - 1][0]);
	// ft_printf("I write to fd[%d]", data->pipe_end[i][1]);
	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	close(data->pipe_end[i][1]);



	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
