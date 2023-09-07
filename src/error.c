/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:23:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/07 13:47:48 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*custom_strerror(int err_code)
{
	if (err_code == INV_ENV)
		return ("invalid env");
	if (err_code == INV_ARG)
		return ("invalid argument");
	if (err_code == CMD_NOT_FOUND)
		return ("command not found");
	return ("unknow error");
}

void	error(char *s, int err_code)
{
	char	*err_str;

	err_str = NULL;
	if (err_code < 107)
		err_str = strerror(err_code);
	else
		err_str = custom_strerror(err_code);
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(err_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s, 2);
}

void	exit_error(t_pipe *data, char *s, int err_code)
{
	error(s, err_code);
	if (data)
		free_data(data);
	exit(err_code);
}
