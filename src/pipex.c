/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 15:24:13 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/03 17:13:50 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_pipe	data;

	if (argc != 5)
		return (msg(ERR_INPUT));
	data.infile = open(argv[1], O_RDONLY);
	if (data.infile < 0)
		msg_error(ERR_INFILE, &data);
	data.outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR, 0000644);
	if (data.outfile < 0)
		msg_error(ERR_OUTFILE, &data);
	if (pipe(data.pipe) < 0)
		msg_error(ERR_PIPE, &data);
	data.paths = find_path(envp);
	data.cmd_paths = ft_split(data.paths, ':');
	data.pid1 = fork();
	if (data.pid1 == 0)
		first_child(data, argv, envp);
	data.pid2 = fork();
	if (data.pid2 == 0)
		second_child(data, argv, envp);
	close_all(&data);
	waitpid(data.pid1, NULL, 0);
	waitpid(data.pid2, NULL, 0);
	parent_free(&data);
	return (0);
}
