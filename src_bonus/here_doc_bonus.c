/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 11:42:25 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/04 12:44:15 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	get_here_doc(t_pipe *data)
{
	int		are_s_equal;
	int		here_doc;
	char	*new_line;
	char	*eof;

	eof = data->eof;
	new_line = NULL;
	here_doc = open("here_doc", O_RDWR | O_CREAT | O_APPEND, 0644);
	if (here_doc == -1)
		exit_error(data, "open()", errno);
	ft_putstr_fd("here_doc>", 1);
	while (1)
	{
		if (new_line)
			free(new_line);
		new_line = get_next_line(0);
		are_s_equal = ft_strncmp(new_line, eof, ft_strlen(eof));
		if (!are_s_equal) // eof
			break ;
		else
		{
			ft_putstr_fd(new_line, here_doc);
			ft_putstr_fd("here_doc>", 1);
		}
	}
	if (new_line)
		free(new_line);
	// if nothing is written inhere_doc????
	return (here_doc);
}




// t_list	*get_stdin(char *eof)
// {
// 	t_list	*new_line;
// 	t_list	*here_doc;
// 	int		are_s_equal;

// 	new_line = NULL;
// 	here_doc = NULL;
// 	ft_putstr_fd("here_doc>", 1);
// 	while (1)
// 	{
// 		new_line = ft_lstnew((char *) get_next_line(0));
// 		ft_lstadd_back(&here_doc, new_line);
// 		are_s_equal = ft_strncmp(new_line->content, eof, ft_strlen(eof));
// 		if (!are_s_equal) // eof
// 			break ;
// 		else
// 			ft_putstr_fd("here_doc>", 1);
// 	}
// 	return (here_doc);
// }
