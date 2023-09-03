/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 19:28:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* int i is the index of the process necessary to remember which pipe close */
void	first_child(t_pipe *data, int i, char **env)
{
	int	fd_infile;

	sleep(1);
	ft_printf("\n[FIRST]\n");
	ft_printf("[%s]\n", data->cmd[i][0]);

	ft_printf("I close() fd that I don't need:\n");
	int	j;
	j = data->n_cmd - 1;
	while (j > 0)
	{
		close(data->pipe_end[j][0]);
		close(data->pipe_end[j][1]);
		j--;
	}

	// close the current pipe-read
	close(data->pipe_end[i][0]);
	fd_infile = open(data->infile, O_RDONLY);
	if (fd_infile == -1)
		exit_error(data, data->infile, errno);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	ft_printf("I read from [%s] fd[%d]\n", data->infile, fd_infile);

	// redirect to pipe-write
	ft_printf("I write to fd[%d]\n", data->pipe_end[i][1]);
	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1) // remove to see output
		exit_error(data, "dup2()", errno);

	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}











// void	first_child(t_pipe *data, int i, char **env)
// {
// 	int	fd_infile;

// 	sleep(1);
// 	ft_printf("\n[FIRST]\n");
// 	ft_printf("[%s]\n", data->cmd[i][0]);
// 	ft_printf("I had the new pipe [%d] ", i);
// 	ft_printf("with fd [%d][%d]\n", data->pipe_end[i][0], data->pipe_end[i][1]);

// 	fd_infile = open(data->infile, O_RDONLY);
// 	if (fd_infile == -1)
// 		exit_error(data, data->infile, errno);
// 	ft_printf("I read from [%s] fd[%d]\n", data->infile, fd_infile);

// 	ft_printf("I have to close fd[%d]\n", data->pipe_end[i][0]);
// 	close(data->pipe_end[i][0]);
// 	ft_printf("I write to fd[%d]\n", data->pipe_end[i][1]);

// 	if (dup2(fd_infile, STDIN_FILENO) == -1)
// 		exit_error(data, "dup2()", errno);
// 	close(fd_infile);
// 	if (dup2(data->pipe_end[i][1], STDOUT_FILENO) == -1) // remove to see output
// 		exit_error(data, "dup2()", errno);
// 	close(data->pipe_end[i][1]);


// 	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
// 		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
// }
