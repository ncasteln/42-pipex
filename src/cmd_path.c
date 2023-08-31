/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:09:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 13:41:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Returns the PATH env variable if exist, otherwise NULL. Only the value of
the variable is returned (its name is trimmed) */
char *get_path_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 4))
			return (env[i] + 5);
		i++;
	};
	return (NULL);
}

char** find_cmd(char *cmd1, char *cmd2, char *path_env) // assumes that the cmds are 2
{
	// 1) find cmd1 and cmd2 using the path_env variable
	// 2) if it finds it, it prefix with abs path, if not it set it NULL
	// 3) the cmcds are collected in an array

	char	**path;
	int		i;

	ft_printf("[PATH] %s", path_env);
	path = ft_split(path_env, ':');
	i = 0;
	while (path[i])
	{
		ft_printf("%s\n", path[i]);
		i++;
	}

	// while (access(path[i], F_OK) == -1)
	// {
	// 	ft_printf("Not found in %s\n");
	// 	i++;
	// }



}
