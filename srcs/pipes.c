/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:29:57 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/25 02:13:23 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	dup_pipes(int *pipe_open, t_cmd *cmd)
{
	if (cmd->is_piped && dup2(cmd->pipes[1], 1) < 0)
		return (0);
	if (cmd->prev && cmd->prev->is_piped
		&& dup2(cmd->prev->pipes[0], 0) < 0)
		return (0);
	ft_dup_fd(cmd);
	*pipe_open = 1;
	return (1);
}

int	close_pipes(int pipe_open, t_cmd *cmd)
{
	t_file_list *f;

	f = cmd->file;
	while (f)
	{
		if (f->type == RR_INPUT)
		{
			close(f->pipes[0]);
			close(f->pipes[1]);
		}
		f = f->next;
	}
	if (cmd->prev && cmd->prev->is_piped == 1)
		close(cmd->prev->pipes[0]);
	if (!pipe_open)
		return (1);
	close(cmd->pipes[1]);
	if (!cmd->next)
		close(cmd->pipes[0]);
	return (1);
}
