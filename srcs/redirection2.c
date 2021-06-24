/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:55:19 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 22:12:25 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc(t_file_list *f)
{
	dup2(f->pipes[0], 0);
	close(f->pipes[0]);
	return (1);
}

void	ft_dup_fd(t_cmd *cmd)
{
	t_file_list	*f;

	f = cmd->file;
	while (f)
	{
		if (f->type == R_OUTPUT || f->type == RR_OUTPUT)
			dup2(f->fd, 1);
		else if (f->type == R_INPUT || f->type == RR_INPUT)
		{
			if (f->type == R_INPUT)
				dup2(f->fd, 0);
			if (f->type == RR_INPUT)
				ft_heredoc(f);
		}
		f = f->next;
	}
}
