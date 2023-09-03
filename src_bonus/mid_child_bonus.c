/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mid_child_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 17:38:39 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 19:32:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	mid_child(t_pipe *data, int i, char **env)
{
	sleep(i + i); // just to wait
	ft_printf("\n[MID]\n");
	ft_printf("[%s]\n", data->cmd[i][0]);

	ft_printf("I close() fd that I don't need:\n");
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


	ft_printf("I read from fd[%d]\n", data->pipe_end[i - 1][0]);
	dup2(data->pipe_end[i - 1][0], STDIN_FILENO);
	close(data->pipe_end[i - 1][0]);
	ft_printf("I write to fd[%d]", data->pipe_end[i][1]);
	dup2(data->pipe_end[i][1], STDOUT_FILENO);
	close(data->pipe_end[i][1]);



	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
}







// void	mid_child(t_pipe *data, int i, char **env)
// {
// 	sleep(i + i); // just to wait
// 	ft_printf("\n[MID]\n");
// 	ft_printf("[%s]\n", data->cmd[i][0]);
// 	ft_printf("I use pipe number [%d] ", i);
// 	ft_printf("with fd [%d][%d]\n", data->pipe_end[i][0], data->pipe_end[i][1]);

// 	ft_printf("I know a lot of pipes which I should close.\n");
// 	print_pipe_end(data->pipe_end, data->n_cmd);

// 	ft_printf("I read from fd[%d]\n", data->pipe_end[i - 1][0]);
// 	dup2(data->pipe_end[i - 1][0], STDIN_FILENO);
// 	ft_printf("I write to fd[%d]", data->pipe_end[i][1]);
// 	dup2(data->pipe_end[i][1], STDOUT_FILENO);

// 	ft_printf("I also have to close() other fd:\n");
// 	int	j = 0;
// 	while (j < i) // (0 < 2)
// 	{
// 		if (j == (i - 1)) // just close the read end of the last
// 		{
// 			close(data->pipe_end[j][1]);
// 			ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
// 		}
// 		else // close unuseful fds if exist
// 		{
// 			if (data->pipe_end[j][0] != -1)
// 			{
// 				close(data->pipe_end[j][0]);
// 				ft_printf("close(fd[%d])\n", data->pipe_end[j][0]);
// 			}
// 			if (data->pipe_end[j][1] != -1)
// 			{
// 				close(data->pipe_end[j][1]);
// 				ft_printf("close(fd[%d])\n", data->pipe_end[j][1]);
// 			}
// 		}
// 		j++;
// 	}
// 	close(data->pipe_end[j][0]);
// 	ft_printf("close(fd[%d])\n", data->pipe_end[j][0]);

// 	if (execve(data->cmd[i][0], data->cmd[i], env) == -1)
// 		exit_error(data, data->cmd[i][0], CMD_NOT_FOUND);
// }
