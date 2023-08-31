/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:09:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 18:18:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_cmd(char *arg, char **path) // assumes that the cmds are 2
{
	char	**cmd;
	char	*abs_path;
	char	*temp;
	int		i;

	abs_path = NULL;
	i = 0;

	cmd = ft_split(arg, ' ');
	if (access(cmd[0], F_OK) == 0)
		return (cmd);
	while (path[i])
	{
		abs_path = ft_strjoin(path[i], "/"); // check if leave traces
		temp = ft_strdup(abs_path);
		free(abs_path);
		abs_path = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (access(abs_path, F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = abs_path;
			return (cmd); // return NULL | cmd | 127 ????????????
		}
		i++;
	}
	return (free(abs_path), cmd); // return NULL | cmd | 127 ????????????
}







// void find_cmd(char *cmd, char **path) // assumes that the cmds are 2
// {
// 	char	*abs_path;
// 	char	*temp;
// 	int		i;

// 	abs_path = NULL;
// 	i = 0;

// 	if (access(cmd, F_OK) == 0)
// 		return ;
// 	while (path[i])
// 	{
// 		abs_path = ft_strjoin(path[i], "/"); // check if leave traces
// 		temp = ft_strdup(abs_path);
// 		free(abs_path);
// 		abs_path = ft_strjoin(temp, cmd);
// 		free(temp);
// 		if (access(abs_path, F_OK) == 0)
// 		{
// 			free(cmd);
// 			cmd = abs_path;
// 			return ;
// 		}
// 		i++;
// 	}
// 	free(cmd);
// }
