/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:46:19 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/03 17:17:29 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	parent_free(t_pipe *data, int argc)
{
	int	i;

	i = 0;
	close(data->infile);
	close(data->outfile);
	if (data->doc == 1 && unlink(".here_doc") == -1)
		msg_error(ERR_UNLINK, data);
	while (data->cmd_paths[i])
	{
		free(data->cmd_paths[i]);
		i++;
	}
	free(data->cmd_paths);
	free(data->pipe);
	free(data->pid);
	close(argc - 1);
	close(6);
	close(5);
}

void	child_free(t_pipe *data)
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
	free(data->pipe);
	free(data->pid);
}
