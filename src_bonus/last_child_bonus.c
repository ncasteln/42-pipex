/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/04 14:09:18 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	last_child(t_pipe *data, int i, char **env)
{
	int	fd_outfile;

	ft_printf("\n__LAST CHILD__\n");
	ft_printf("I know the following FD:\n");
	print_pipe_end(data);
	int	j;
	j = data->n_cmd - 1;
	while (j >= 0)
	{
		if (j == (i - 1))
		{
			// close only write
			ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
			close(data->pipe_end[j][1]);
		}
		else if (j != i)
		{
			ft_printf("close(fd[%d])\n", data->pipe_end[j][0]);
			ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
		}
		j--;
	}
	close(data->pipe_end[i - 1][1]);

	// ft_printf("I read from fd[%d]\n", data->pipe_end[i - 1][0]);
	dup2(data->pipe_end[i - 1][0], STDIN_FILENO);
	close(data->pipe_end[i - 1][0]);

	if (data->here_doc)
		fd_outfile = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_outfile = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_outfile == -1)
		exit_error(data, data->outfile, errno);
	dup2(fd_outfile, STDOUT_FILENO);
	close(fd_outfile);

	close(data->here_doc);

	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
