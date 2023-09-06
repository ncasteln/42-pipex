/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 12:14:06 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/*
	WIFSIGNALED can be check only in case of a cmd which run a program (like
	"ping"). To send a signal use "kill -sig_n pid"
*/
static int	check_wstatus(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	return (0);
}

static int	wait_children(pid_t *ps_id, int n_cmd)
{
	int		wstatus;
	int		exit_code;
	pid_t	w_pid;
	int		i;

	exit_code = 0;
	i = 0;
	while (i < n_cmd)
	{
		w_pid = waitpid(ps_id[i], &wstatus, 0);
		if (w_pid == ps_id[i])
			exit_code = check_wstatus(wstatus);
		i++;
	}
	return (exit_code);
}

static void	close_all(t_pipe *data)
{
	int	j;

	j = data->n_cmd - 2;
	while (j >= 0)
	{
		close(data->pipe_end[j][0]);
		close(data->pipe_end[j][1]);
		j--;
	}
	close(data->fd_infile);
	close(data->fd_outfile);
}

int	parent(t_pipe *data)
{
	int	last_exit_code;

	close_all(data);
	last_exit_code = wait_children(data->ps_id, data->n_cmd);
	free_data(data);
	return (last_exit_code);
}
