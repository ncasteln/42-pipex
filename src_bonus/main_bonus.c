/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncasteln <ncasteln@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 11:13:58 by ncasteln          #+#    #+#             */
/*   Updated: 2023/09/05 17:25:15 by ncasteln         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	parse_data(t_pipe *data, int argc, char **argv, char **env)
{
	if (argc < 5)
		exit_error(NULL, "argc", INV_ARG);

	// HERE DOC & EOF
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		data->here_doc = 1;
	if (data->here_doc)
	{
		if (argc < 6)
			exit_error(data, "argc", INV_ARG);
		data->eof = argv[2];
	}

	// N_CMDS
	data->n_cmd = argc - 3;
	if (data->here_doc)
		data->n_cmd = argc - 4;

	// IN AND OUTFILES
	data->infile = argv[1];
	data->outfile = argv[argc - 1];

	// FD
	create_fd(data);

	// PATH & CMDS
	data->path = get_env_path(env);
	data->cmd = parse_all_cmd(data, argv);

	// PID COLLECTION
	data->ps_id = malloc(sizeof(pid_t) * data->n_cmd);
	if (!data->ps_id)
		exit_error(data, "malloc()", errno);
}

/* int i is necessary to to send every child the information about the number
of process they are (like an id), so that they know if they are the first,
the mid or the last one */
int	main(int argc, char **argv, char **env)
{
	t_pipe	data;
	int		i;

	init_data(&data);
	parse_data(&data, argc, argv, env);
	i = 0;
	while (i < data.n_cmd)
	{
		data.ps_id[i] = fork();
		if (data.ps_id[i] == -1)
			exit_error(&data, "fork()", errno);
		else if (data.ps_id[i] == 0)
		{
			if (i == 0)
				first_child(&data, 0, env);
			else if (i == data.n_cmd - 1)
				last_child(&data, i, env);
			else
				mid_child(&data, i, env);
		}
		else
			i++;
	}
	return (parent(&data));
}
