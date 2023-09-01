/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 17:53:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_wstatus(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	if (WIFSTOPPED(wstatus))
		return (WSTOPSIG(wstatus));
	// if (WIFCONTINUED(wstatus))
	return (0);
}

int	wait_children(t_data data, int id_1, int id_2)
{
	int		wstatus;
	int		exit_code;
	pid_t	w_pid;

	exit_code = 0;

	w_pid = waitpid(id_1, &wstatus, 0);
	if (w_pid == id_1)
		exit_code = check_wstatus(wstatus);

	w_pid = waitpid(id_2, &wstatus, 0);
	if (w_pid == id_2)
		exit_code = check_wstatus(wstatus);

	return (exit_code);
}

int	parent(t_data data, pid_t id_1, pid_t id_2, int *pipe_end)
{
	int	last_exit_code;

	close(pipe_end[0]); // /dev/urandom ---> !!!
	close(pipe_end[1]);
	last_exit_code = wait_children(data, id_1, id_2);
	return (last_exit_code);
}
