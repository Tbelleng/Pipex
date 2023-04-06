/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:56 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/03 17:15:48 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*find_path(char **envp)
{
	int	i;
	int	no_path;

	i = 0;
	no_path = 0;
	if (!envp[0])
	{
		msg(NO_PATH);
		exit(1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strnstr(envp[i], "PATH", 6) != NULL)
			no_path = 1;
		i++;
	}
	if (no_path == 0)
	{
		msg(NO_PATH);
		exit(1);
	}
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	new_pipe(t_pipe *data, int argc)
{
	int	i;

	i = 0;
	data->cmd_nb = argc - 3 - data->doc;
	while (i < data->cmd_nb - 1)
	{
		if (pipe(data->pipe + (2 * i)) < 0)
			parent_free(data, argc);
		i++;
	}
}

void	end_main(t_pipe data, int argc, char **envp, char **argv)
{
	int	i;

	i = 0;
	while (data.pidx < data.cmd_nb)
	{
		multiple_cmd(data, argv, envp);
		data.pidx++;
	}
	close_pipes(&data);
	while (i < data.cmd_nb)
	{
		waitpid(data.pid[i], NULL, 0);
		i++;
	}
	parent_free(&data, argc);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipe	data;

	if (argc - 1 < 4)
		msg_error(ERR_INPUT, &data);
	is_heredoc(argv, &data);
	if (data.infile < 0)
		msg_error(ERR_INFILE, &data);
	data.outfile = out_file(argc, argv, &data);
	if (data.outfile < 0)
		msg_error(ERR_OUTFILE, &data);
	data.pipe_nb = 2 * ((argc - 3 - data.doc) - 1);
	data.pipe = malloc(sizeof(int *) * data.pipe_nb);
	if (pipe(data.pipe) < 0)
		msg_error(ERR_PIPE, &data);
	data.paths = find_path(envp);
	data.cmd_paths = ft_split(data.paths, ':');
	new_pipe(&data, argc);
	data.pid = malloc(sizeof(pid_t) * (data.cmd_nb));
	if (!data.pid)
		pid_err(&data, argc);
	end_main(data, argc, envp, argv);
	return (0);
}
