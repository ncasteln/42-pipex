/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:41:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 11:43:17 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	// {
	// 	int i = 0;
	// 	while (i < (data->n_cmd - 1))
	// 	{
	// 		free(data->pipe_end[i]);
	// 		i++;
	// 	}
	// }
	// if (data->here_doc)
	// {
	// 	if (unlink("here_doc") == -1)
	// 		error("unlink()", errno);
	// }
	init_data(data);
}
