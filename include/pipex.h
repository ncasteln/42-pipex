/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/08/31 18:32:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h> // perror
#include <errno.h>

typedef struct s_data
{
	char	*shell;
	char	*in_file;
	char	*out_file;
	char	**path;
	char	**cmd1;
	char	**cmd2;
}				t_data;

// -------------------------------------------------------------------- PARSING
char	*get_shell(char **env);
char	**get_path(char **env);
char	**find_cmd(char *cmd, char **path);

// -------------------------------------------------------------------- FORKING
int		first_child(t_data data, int *fd_pipe, char **env);
void	last_child(void);
int		parent(void);


#endif
