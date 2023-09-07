/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:41:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 09:29:45 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(t_pipe *data)
{
	int	i;

	close(data->fd_infile);
	close(data->fd_outfile);
	i = data->n_cmd - 2;
	while (i >= 0)
	{
		close(data->pipe_end[i][0]);
		close(data->pipe_end[i][1]);
		i--;
	}
}

void	init_data(t_pipe *data)
{
	data->ps_id = NULL;
	data->pipe_end = NULL;
	data->path = NULL;
	data->n_cmd = 0;
	data->cmd = NULL;
	data->infile = NULL;
	data->outfile = NULL;
	data->fd_infile = -1;
	data->fd_outfile = -1;
	data->here_doc = 0;
	data->eof = NULL;
}

static void	free_dptr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static void	free_tptr(char ***s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free_dptr(s[i]);
		i++;
	}
	free(s);
}

void	free_data(t_pipe *data)
{
	if (data->ps_id)
		free(data->ps_id);
	if (data->path)
		free_dptr(data->path);
	if (data->cmd)
		free_tptr(data->cmd);
	if (data->pipe_end)
		free(data->pipe_end);
	init_data(data);
}
