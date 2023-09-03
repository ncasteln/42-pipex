/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:09:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 11:15:27 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_abs_path(char *path, char *cmd)
{
	char	*abs_path;
	char	*temp;

	abs_path = ft_strjoin(path, "/");
	temp = abs_path;
	abs_path = ft_strjoin(abs_path, cmd);
	free(temp);
	return (abs_path);
}

static int	is_empty_str(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] == ' ')
		i++;
	if (i == ft_strlen(s))
		return (1);
	return (0);
}

char	**find_cmd(char *arg, char **path)
{
	char	**cmd;
	char	*abs_path;
	int		i;

	abs_path = NULL;
	i = 0;
	if (is_empty_str(arg))
		return (NULL);
	cmd = ft_split(arg, ' ');
	if (access(cmd[0], F_OK) == 0)
		return (cmd);
	while (path[i])
	{
		if (abs_path)
			free(abs_path);
		abs_path = get_abs_path(path[i], cmd[0]);
		if (access(abs_path, F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = abs_path;
			return (cmd);
		}
		i++;
	}
	return (cmd);
}
