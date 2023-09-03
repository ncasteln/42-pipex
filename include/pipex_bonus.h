/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:08 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 18:10:23 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h> // strerror()

typedef struct s_pipe
{
	pid_t	*ps_id;
	int		(*pipe_end)[2];
	char	*infile;
	char	*outfile;
	char	**path;
	int		n_cmd;
	char	**cmd1; // remove
	char	**cmd2; // remove
	char	***cmd;
}				t_pipe;

// -------------------------------------------------------------------- PARSING
char	**get_env_path(char **env);
char	***parse_all_cmd(t_pipe *data, char **argv);
char	**parse_single_cmd(char *arg, char **path);

// -------------------------------------------------------------------- FORKING
void	first_child(t_pipe *data, int i, char **env);
void	mid_child(t_pipe *data, int i, char **env);
void	last_child(t_pipe *data, int i, char **env);
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
void	print_pipe_end(int (*pipe_end)[2], int n_cmd);

#endif
