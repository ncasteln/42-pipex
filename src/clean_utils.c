/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 09:16:50 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 09:19:22 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_pipe *data)
{
	data->ps_id = NULL;
	data->path = NULL;
	data->cmd1 = NULL;
	data->cmd2 = NULL;
	data->infile = NULL;
	data->outfile = NULL;
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

void	free_data(t_pipe *data)
{
	if (data->ps_id)
		free(data->ps_id);
	if (data->path)
		free_dptr(data->path);
	if (data->cmd1)
		free_dptr(data->cmd1);
	if (data->cmd2)
		free_dptr(data->cmd2);
}
