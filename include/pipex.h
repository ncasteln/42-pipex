/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 17:15:44 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include "libft.h"
#include "ft_printf.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <errno.h>
#include <stdio.h> // perror()
#include <string.h> // strerror()

typedef struct s_data
{
	// pid_t	*sub_ps;
	char	*infile;
	char	*outfile;
	char	**path;
	char	**cmd1;
	char	**cmd2;
}				t_data;

// --------------------------------------------------------------------- ERRORS
enum e_custom_err
{
	CMD_NOT_FOUND = 127
};
void	error(char *s, int err_code);

// -------------------------------------------------------------------- PARSING
char	**get_path(char **env);
char	**find_cmd(char *cmd, char **path);

// -------------------------------------------------------------------- FORKING
void	first_child(t_data data, int *fd_pipe, char **env);
void	last_child(t_data data, int *fd_pipe, char **env);
int		parent(t_data data, pid_t id_1, pid_t id_2, int *pipe_end);
int		wait_children(t_data data, int id_1, int id_2);

#endif
