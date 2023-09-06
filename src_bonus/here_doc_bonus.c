/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:42:25 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 11:44:02 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*build_prompt_prefix(int n_pipes)
{
	char	*prompt;
	char	*temp;

	temp = NULL;
	prompt = NULL;
	while (n_pipes)
	{
		if (!prompt)
			prompt = ft_strdup("pipe ");
		else
		{
			temp = prompt;
			prompt = ft_strjoin(prompt, "pipe ");
			free(temp);
		}
		n_pipes--;
	}
	temp = prompt;
	prompt = ft_strjoin(prompt, "heredoc>");
	free(temp);
	return (prompt);
}

void	get_prompt(t_pipe *data)
{
	int		are_s_different;
	char	*new_line;
	char	*prompt;

	new_line = NULL;
	prompt = build_prompt_prefix(data->n_cmd - 1);
	ft_putstr_fd(prompt, 1);
	while (1)
	{
		if (new_line)
			free(new_line);
		new_line = get_next_line(STDIN_FILENO);
		are_s_different = ft_strncmp(new_line, data->eof, ft_strlen(data->eof));
		if (!are_s_different)
			break ;
		else
		{
			ft_putstr_fd(new_line, data->fd_infile);
			ft_putstr_fd(prompt, 1);
		}
	}
	if (new_line)
		free(new_line);
	free(prompt);
}
