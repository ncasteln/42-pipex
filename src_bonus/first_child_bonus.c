/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/05 11:11:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* int i is the index of the process necessary to remember which pipe close */
void	first_child(t_pipe *data, int i, char **env)
{
	ft_printf("__FIRST CHILD__\n");
	// ft_printf("I know these FD:\n");
	// print_fd(data);
	// ft_printf("\n");
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
	ft_printf("Read from fd[%d]\n", data->fd_infile);
	if (dup2(data->fd_infile, STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	// i write to
	ft_printf("Write to fd[%d]\n", data->pipe_end[i][1]);
	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);

	// i close unnecessary fd
	if (data->n_cmd > 2)
	{
		int	j;
		j = data->n_cmd - 2;
		while (j > 0)
		{
			// ft_printf("close(fd[%d])\n", data->pipe_end[j][0]);
			// ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
			close(data->pipe_end[j][0]);
			close(data->pipe_end[j][1]);
			j--;
		}
	}
	// ft_printf("close(fd[%d])\n", data->fd_infile);
	close(data->fd_infile);
	// ft_printf("close(fd[%d])\n", data->pipe_end[i][0]);
	close(data->pipe_end[i][0]);
	// ft_printf("close(fd[%d])\n", data->pipe_end[i][1]);
	close(data->pipe_end[i][1]);

	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}
