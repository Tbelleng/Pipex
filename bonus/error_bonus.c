/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbelleng <tbelleng@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:53:49 by tbelleng          #+#    #+#             */
/*   Updated: 2023/04/03 17:16:24 by tbelleng         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

int	msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	msg_error(char *err, t_pipe *data)
{
	perror(err);
	close(data->infile);
	exit(1);
}

void	close_pipes(t_pipe *data)
{
	int	i;

	i = 0;
	while (i < (data->pipe_nb))
	{
		close(data->pipe[i]);
		i++;
	}
}

void	close_all(t_pipe *data)
{
	close(data->pipe[0]);
	close(data->pipe[1]);
	close(data->outfile);
	close(data->infile);
	free(data->pipe);
}

void	pid_err(t_pipe *data, int argc)
{
	parent_free(data, argc);
	exit(0);
}
