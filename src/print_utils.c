/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:45:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 14:29:19 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_cmd(char **cmd)
{
	int	i;

	i = 0;
	ft_printf("_COMMANDS STORED_\n");
	while (cmd[i])
	{
		ft_printf("[%s]\n", cmd[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_pid(int *p, int n_cmd)
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
