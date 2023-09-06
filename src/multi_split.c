/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 15:17:22 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/06 17:22:57 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	populate_lst(t_list **lst, char **cmd)
{
	int		i;
	t_list	*new_node;

	i = 0;
	new_node = NULL;
	while (cmd[i])
	{
		new_node = ft_lstnew(ft_strdup(cmd[i]));
		if (new_node)
			ft_lstadd_back(lst, new_node);
		i++;
	}
}

static void	free_dptr(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]); // chane this function is duplicate!!
		i++;
	}
	free(s);
}

char	**multi_split(char *arg)
{
	int		n_quotes;
	size_t	i;

	n_quotes = 0;
	i = 0;
	while (i < ft_strlen(arg))
	{
		if (arg[i] == '\'')
			n_quotes++;
		i++;
	}

	// n_quote times

}






// char	**multi_split(char *arg)
// {
// 	t_list	*lst;
// 	char	**cmd;

// 	lst = NULL;
// 	cmd = ft_split(arg, '\'');
// 	print_cmd(cmd);
// 	if (!cmd)
// 		return (NULL);
// 	populate_lst(&lst, cmd);
// 	free_dptr(cmd);


// 	ft_printf("LIST[0] %s\n", lst->content);
// 	ft_printf("LIST[1] %s\n", lst->next->content);
// 	// ft_printf("LIST[2] %s\n", lst->next->next->content);
// 	// ft_printf("LIST[3] %s\n", lst->next->next->next->content);



// 	t_list	*new_top;
// 	t_list	*old_top;
// 	t_list	*new_node;
// 	t_list	*new_list;

// 	old_top = lst;
// 	new_top = lst;
// 	while (ft_strchr(lst->content, ' '))
// 	{
// 		// split
// 		cmd = ft_split(lst->content, ' ');
// 		// check fail
// 		// remove new_top
// 		// // store splitted strings and remaining
// 		int n_cmds_to_add = 0;
// 		int	i;

// 		while (cmd[n_cmds_to_add])
// 			n_cmds_to_add++;
// 		i = n_cmds_to_add;
// 		n_cmds_to_add--;
// 		while (n_cmds_to_add >= 0)
// 		{
// 			new_node = ft_lstnew(ft_strdup(cmd[n_cmds_to_add]));
// 			ft_lstadd_front(&lst, new_node);
// 			n_cmds_to_add--;
// 		}
// 		free_dptr(cmd);

// 		new_top = lst; // remember the new cmd adress
// 		while (i > 0)
// 		{
// 			ft_printf("I dont want clear [%s]\n", lst->content);
// 			lst = lst->next;
// 			i--;
// 		}
// 		ft_printf("but i want clear [%s]\n", lst->content);
// 		ft_bzero(lst->content, ft_strlen(lst->content));
// 		free(lst->content);
// 		lst->content = NULL;

// 		lst = new_top;
// 		// empty string???
// 	}


// 	ft_printf("HEY { %s }\n", lst->content);
// 	ft_printf("HEY { %s }\n", lst->next->content);
// 	ft_printf("HEY { %s }\n", lst->next->next->content);
// 	ft_printf("HEY { %s }\n", lst->next->next->next->content);

// 	lst = new_top;
// 	// convert to dptr
// 	int	n_flags;
// 	int i;

// 	i = 0;
// 	n_flags = ft_lstsize(lst);
// 	cmd = malloc (sizeof(char *) * (n_flags + 1));
// 	cmd[n_flags] = NULL;
// 	while (lst)
// 	{
// 		if (lst->content)
// 		{
// 			ft_printf("copy { %s } ", lst->content);
// 			ft_printf("allocate for %d char\n", ft_strlen(lst->content));
// 			cmd[i] = malloc (sizeof(char) * (ft_strlen(lst->content) + 1));
// 			cmd[i][ft_strlen(lst->content)] = '\0';
// 			ft_memcpy(cmd[i], lst->content, ft_strlen(lst->content));
// 		}
// 		lst = lst->next;
// 		i++;
// 	}

// 	// free lst
// 	ft_printf("CMD[0] %s \n", cmd[0]);
// 	ft_printf("CMD[1] %s \n", cmd[1]);
// 	ft_printf("CMD[2] %s \n", cmd[2]);
// 	ft_printf("CMD[3] %s \n", cmd[3]);

// 	return (cmd);
// }
