/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:41:40 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 21:42:43 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
}
