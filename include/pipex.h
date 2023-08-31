/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 13:35:28 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"

typedef struct s_data
{
	int		in_file;
	int		out_file;
	char	*path_env;
	char	**cmd;
}				t_data;

char	*get_path_env(char **env);
char**	find_cmd(char *cmd1, char *cmd2, char *path_env);

#endif
