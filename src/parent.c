/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 11:52:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

static int	wait_children(int id_1, int id_2)
{
	int		wstatus;
	int		exit_code;
	pid_t	w_pid;

	exit_code = 0;
	w_pid = waitpid(id_1, &wstatus, 0);
	if (w_pid == id_1)
		exit_code = check_wstatus(wstatus);
	else if (w_pid == -1)
		error("waitpid()", errno);
	w_pid = waitpid(id_2, &wstatus, 0);
	if (w_pid == id_2)
		exit_code = check_wstatus(wstatus);
	else if (w_pid == -1)
		error("waitpid()", errno);
	return (exit_code);
}

int	parent(t_pipe *data, int *pipe_end)
{
	int	last_exit_code;

	close(pipe_end[0]);
	close(pipe_end[1]);
	last_exit_code = wait_children(data->ps_id[0], data->ps_id[1]);
	free_data(data);
	return (last_exit_code);
}
