/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 11:14:42 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	last_child(t_data *data, int *pipe_end, char **env)
{
	int	outfile;

	if (close(pipe_end[1]))
		exit_error(data, "close()", errno);
	outfile = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		exit_error(data, data->outfile, errno);
	if (dup2(pipe_end[0], STDIN_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (close(pipe_end[0]))
		exit_error(data, "close()", errno);
	if (dup2(outfile, STDOUT_FILENO) == -1)
		exit_error(data, "dup2()", errno);
	if (close(outfile))
		exit_error(data, "close()", errno);
	if (execve(data->cmd2[0], data->cmd2, env) == -1)
		exit_error(data, data->cmd2[0], CMD_NOT_FOUND);
}
