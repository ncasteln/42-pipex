/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/01 13:23:26 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/01 17:19:13 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*custom_strerror(int err_code)
{
	if (err_code == 127)
		return ("command not found");
	return ("unknow error");
}

void	error(char *s, int err_code)
{
	char	*err_str;

	err_str = NULL;
	if (err_code < 107)
		err_str = strerror(errno);
	else
		err_str = custom_strerror(err_code);
	ft_putstr_fd("zsh: ", 2);
	ft_putstr_fd(err_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s, 2);
}
