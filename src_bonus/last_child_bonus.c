/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 20:39:55 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_pipe *data, int i, char **env)
{
	int	fd_outfile;

	// sleep(6);
	// ft_printf("\n\n[LAST]\n");
	// ft_printf("[%s]\n", data->cmd[i][0]);

	// ft_printf("I close() fd that I don't need:\n");
	int	j;
	j = data->n_cmd - 1;
	while (j >= 0)
	{
		if (j == (i - 1))
		{
			// close only write
			close(data->pipe_end[j][1]);
			// ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
		}
		else if (j != i)
		{
			close(data->pipe_end[j][0]);
			// ft_printf("close(fd[%d])\n", data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
			// ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
		}
		j--;
	}

	// ft_printf("I read from fd[%d]\n", data->pipe_end[i - 1][0]);
	dup2(data->pipe_end[i - 1][0], STDIN_FILENO);
	close(data->pipe_end[i - 1][0]);
	fd_outfile = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		exit_error(data, data->outfile, errno);
	// ft_printf("I write to [%s] fd[%d] ", data->outfile, fd_outfile);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);

	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
