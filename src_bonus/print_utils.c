/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:45:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/03 21:46:41 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_cmd(char ***cmd) //remove
{
	int	i, j;

	i = 0;
	ft_printf("_COMMANDS STORED_\n");
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			ft_printf("[%s]", cmd[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	print_pid(int *p, int n_cmd) //remove
{
	int	i;

	i = 0;
	ft_printf("_PS_ID_\n");
	while (i < n_cmd)
	{
		ft_printf("[%d]\n", p[i]);
		i++;
	}
}

void	print_pipe_end(int (*pipe_end)[2], int n_cmd) // remove
{
	int	i;

	i = 0;
	while (i < (n_cmd - 1))
	{
		ft_printf("fd[%d]\n", pipe_end[i][0]);
		ft_printf("fd[%d]\n", pipe_end[i][1]);
		i++;
	}
}
