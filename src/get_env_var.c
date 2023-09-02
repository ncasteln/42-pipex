/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 17:23:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/02 11:35:50 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Check in env the existence of s and return ONLY its value
(the var name is trimmed), otherwise return NULL */
static char *get_env_var(char **env, char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], s, ft_strlen(s)))
			return (env[i] + ft_strlen(s) + 1);
		i++;
	};
	return (NULL);
}

/* Returns the PATH env variable if exist, otherwise NULL. The value of
the str is splitted into sub-strings, as by the delimiter ":" */
char **get_env_path(char **env)
{
	char	*path;

	path = get_env_var(env, "PATH");
	return (ft_split(path, ':'));
}
