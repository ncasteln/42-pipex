/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 13:22:12 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h> // strerror()

typedef struct s_pipe
{
	pid_t	*ps_id;
	char	*infile;
	char	*outfile;
	char	**path;
	char	**cmd1;
	char	**cmd2;
}				t_pipe;

// -------------------------------------------------------------------- PARSING
char	**get_env_path(char **env);
char	**parse_cmd(char *cmd, char **path);

// -------------------------------------------------------------------- FORKING
void	first_child(t_pipe *data, int *fd_pipe, char **env);
void	last_child(t_pipe *data, int *fd_pipe, char **env);
int		parent(t_pipe *data, int *pipe_end);

// ---------------------------------------------------------------------- UTILS
void	free_data(t_pipe *data);

// --------------------------------------------------------------------- ERRORS
enum e_custom_err
{
	INV_ARG = 107,
	CMD_NOT_FOUND = 127,
};
void	error(char *s, int err_code);
void	exit_error(t_pipe *data, char *s, int err_code);

#endif
