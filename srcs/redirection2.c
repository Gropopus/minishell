/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:55:19 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/23 14:39:06 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	ft_heredoc(t_file_list *f)
{
	char *line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, f->path) == 0)
		{
			printf("ici\n");
			dup2(f->fd, 0);
			return (1);
		}
		free(line);
	}
	free(line);
	return (1);
}

void	ft_dup_fd(t_cmd *cmd)
{
	t_file_list *f;

	f = cmd->file;
	while (f)
	{
		if (f->type == R_OUTPUT || f->type == RR_OUTPUT)
			dup2(f->fd, 1);
		else if (f->type == R_INPUT || f->type == RR_INPUT)
		{
			if (f->type == R_OUTPUT)
				dup2(f->fd, 0);
			if (f->type == RR_INPUT)
				ft_heredoc(f);
			printf("michel");
		}
		f = f->next;
	}
}
