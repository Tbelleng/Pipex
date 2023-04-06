/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:31:33 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/03 16:51:47 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	close_all1(t_pipe *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->outfile);
	close(data->infile);
	close(5);
	close(6);
}

void	parent_free1(t_pipe *data)
{
	int	i;

	i = 0;
	close(data->infile);
	close(data->outfile);
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
	free(data->pipe);
	free(data->pid);
}

void	child_free1(t_pipe *data)
{
	int	i;

	i = 0;
	while (data->cmd_args[i])
	{
		free(data->cmd_args[i]);
		i++;
	}
	free(data->cmd_args);
	free(data->cmd);
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
