/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 13:35:05 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	init_data(t_data *data)
{
	data->cmd = NULL;
	data->in_file = -1;
	data->out_file = -1;
	data->path_env = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc < 5)
		return (1);
	init_data(&data);
	data.path_env = get_path_env(env);
	data.cmd = find_cmd(argv[2], argv[3], data.path_env);

	return (0);
}
