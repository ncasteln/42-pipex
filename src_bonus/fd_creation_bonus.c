/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_creation_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:35:20 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 11:54:00 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	no_here_doc(t_pipe *data)
{
	data->fd_infile = open(data->infile, O_RDONLY);
	if (data->fd_infile == -1)
		error(data->infile, errno);
	data->fd_outfile = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_outfile == -1)
		exit_error(data, data->outfile, errno);
}

/*
	here_doc is created with to WRITE and the prompt is taken.
	here_doc is closed to reset the offset, and re-opened to be READ.
*/
static void	here_doc(t_pipe *data)
{
	data->fd_infile = open(data->infile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_infile == -1)
		exit_error(data, "open()", errno);
	get_prompt(data);
	close(data->fd_infile);
	data->fd_infile = open(data->infile, O_RDONLY);
	if (data->fd_infile == -1)
		exit_error(data, "open()", errno);
	if (unlink(data->infile) == -1) //  ------------------------ unlink here ???
		error("unlink() parent", errno);
	data->fd_outfile = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data->fd_outfile == -1)
		exit_error(data, data->outfile, errno);
}

static void	create_pipes(t_pipe *data)
{
	int	i;

	data->pipe_end = malloc(sizeof(int *) * (data->n_cmd));
	if (!data->pipe_end)
		exit_error(data, "malloc()", errno);
	i = 0;
	while (i < (data->n_cmd - 1))
	{
		data->pipe_end[i][0] = -1;
		data->pipe_end[i][1] = -1;
		i++;
	}
	i = 0;
	while (i < (data->n_cmd - 1))
	{
		if (pipe(data->pipe_end[i]) == -1)
			exit_error(data, "pipe()", errno);
		i++;
	}
}

void	create_fd(t_pipe *data)
{
	if (!data->here_doc)
		no_here_doc(data);
	else
		here_doc(data);
	create_pipes(data);
}
