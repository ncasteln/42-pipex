/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 18:31:11 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/02 18:28:59 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	check_wstatus(int wstatus)
{
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	if (WIFSIGNALED(wstatus))
		return (WTERMSIG(wstatus));
	// if (WIFSTOPPED(wstatus))
	// 	return (WSTOPSIG(wstatus));
	// if (WIFCONTINUED(wstatus))
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
	ft_printf("first child: %d\n", exit_code);
	if (id_2 != -1)
	{
		w_pid = waitpid(id_2, &wstatus, 0);
		if (w_pid == id_2)
			exit_code = check_wstatus(wstatus);
	}
	ft_printf("second child: %d\n", exit_code);

	return (exit_code);
}
// #include <signal.h>

// int g_done = 0;

// void handler(int sig)
// {
// 	dprintf(2, "SIGNALED!!!\n");
// 	g_done = 1; (void)sig;
// }

int	parent(pid_t id_1, pid_t id_2, int *pipe_end)
{
	int	last_exit_code;

	// signal(SIGINT, handler);
	close(pipe_end[0]); // /dev/urandom ---> !!!
	close(pipe_end[1]);
	last_exit_code = wait_children(id_1, id_2);

	// while (!g_done)
	// 	g_done = 0;
	// dprintf(2, "FINISHED!!!\n");
	return (last_exit_code);
}
