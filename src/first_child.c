/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_child.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:28:05 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 11:15:25 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data *data, int *pipe_end, char **env)
{
	int	fd_infile;

	if (close(pipe_end[0]) == -1)
		exit_error(data, "close()", errno);
	fd_infile = open(data->infile, O_RDONLY);
	if (fd_infile == -1)
		exit_error(data, data->infile, errno);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (close(fd_infile) == -1)
		exit_error(data, "close()", errno);
	if (dup2(pipe_end[1], STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (close(pipe_end[1]) == -1)
		exit_error(data, "close()", errno);
	if (execve(data->cmd1[0], data->cmd1, env) == -1)
		exit_error(data, data->cmd1[0], CMD_NOT_FOUND);
}
