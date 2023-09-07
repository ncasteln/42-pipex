/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 13:09:04 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 14:39:50 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*build_abs_path(char *path, char *cmd)
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

/* Tries the different paths until something accessible() is found */
static char	*find_cmd(char *cmd, char **path)
{
	char	*abs_path;
	int		i;

	abs_path = NULL;
	i = 0;
	while (path[i])
	{
		if (abs_path)
			free(abs_path);
		abs_path = build_abs_path(path[i], cmd);
		if (access(abs_path, F_OK | X_OK) == 0)
			return (abs_path);
		i++;
	}
	if (abs_path)
		free(abs_path);
	return (NULL);
}

/*
	Verifies if an empty str is passed, if the command is already with its
	abs_path, otherwise it searches using the paths of PATH variable.
*/
char	**parse_single_cmd(char *arg, char **path)
{
	char	**cmd;
	char	*abs_path;

	abs_path = NULL;
	cmd = NULL;
	if (!is_empty_str(arg))
	{
		cmd = ft_split(arg, ' ');
		if (access(cmd[0], F_OK | X_OK) == 0)
			return (cmd);
		abs_path = find_cmd(cmd[0], path);
		if (abs_path)
		{
			free(cmd[0]);
			cmd[0] = abs_path;
			return (cmd);
		}
	}
	return (cmd);
}

char	***parse_all_cmd(t_pipe *data, char **argv)
{
	int	i;
	int	j;

	j = 2;
	if (data->here_doc)
		j++;
	i = 0;
	data->cmd = malloc(sizeof(char **) * (data->n_cmd + 1));
	if (!data->cmd)
		exit_error(data, "malloc()", errno);
	data->cmd[data->n_cmd] = NULL;
	while (i < data->n_cmd)
	{
		data->cmd[i] = parse_single_cmd(argv[i + j], data->path);
		if (!data->cmd[i])
			exit_error(data, "argv", INV_ARG);
		i++;
	}
	return (data->cmd);
}
