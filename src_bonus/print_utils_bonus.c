/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 21:45:54 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 12:14:14 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	print_cmd(char ***cmd)
{
	int	i;
	int	j;

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

void	print_fd(t_pipe *data)
{
	int	i;

	i = 0;
	ft_printf("_HERE_DOC_\n");
	if (data->here_doc)
		ft_printf("[Yes] here_doc\n");
	else
		ft_printf("[No] here_doc\n");
	ft_printf("_IN and OUTFILE_\n");
	ft_printf("fd[%d] (in)\n", data->fd_infile);
	ft_printf("fd[%d] (out)\n", data->fd_outfile);
	ft_printf("_PIPES_CREATED_\n");
	while (i < (data->n_cmd - 1))
	{
		ft_printf("fd[%d] (r)\n", data->pipe_end[i][0]);
		ft_printf("fd[%d] (w)\n", data->pipe_end[i][1]);
		i++;
	}
	ft_printf("\n");
}

void	print_stdin(t_list *stdin)
{
	while (stdin->next)
	{
		ft_printf("%s", stdin->content);
		stdin = stdin->next;
	}
}
