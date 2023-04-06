/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:18:19 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/03 16:49:04 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*get_cmd(char **paths, char *cmd)
{
	char	*tmp;
	char	*command;

	while (*paths)
	{
		tmp = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

void	error_free(t_pipe *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[i] != NULL)
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
}

void	first_child(t_pipe data, char **argv, char **envp)
{
	dup2(data.pipe[1], 1);
	close(data.pipe[0]);
	dup2(data.infile, 0);
	data.cmd_args = ft_split(argv[2], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		child_free(&data);
		close_all(&data);
		parent_free(&data);
		msg(ERR_CMD);
		exit(1);
	}
	close(data.pipe[1]);
	close_all(&data);
	execve(data.cmd, data.cmd_args, envp);
	error_free(&data);
	free(data.cmd);
}

void	second_child(t_pipe data, char **argv, char **envp)
{
	dup2(data.pipe[0], 0);
	close(data.pipe[1]);
	dup2(data.outfile, 1);
	data.cmd_args = ft_split(argv[3], ' ');
	data.cmd = get_cmd(data.cmd_paths, data.cmd_args[0]);
	if (!data.cmd)
	{
		child_free(&data);
		close_all(&data);
		parent_free(&data);
		msg(ERR_CMD);
		exit(1);
	}
	close(data.pipe[0]);
	close_all(&data);
	execve(data.cmd, data.cmd_args, envp);
	error_free(&data);
	free(data.cmd);
}
