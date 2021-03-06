/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 11:55:19 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/25 10:50:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_heredoc(t_file_list *f, int i)
{
	char	*doc;
	char	*line;

	f->fd = open("/tmp/heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (f->fd < 0)
		return (-1);
	while (1)
	{
		line = readline(">");
		if (ft_strcmp(line, f->path) == 0)
		{
			ft_strjoin(doc, "\n");
			write(f->fd, doc, ft_strlen(doc));
			return (1);
		}
		else
		{
			if (i++ == 0)
				doc = ft_strdup(line);
			else
			{
				ft_strjoin(doc, "\n");
				ft_strjoin(doc, line);
			}
		}
	}
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
			{
				ft_heredoc(f, -1);
				close(f->pipes[0]);
			}
		}
		f = f->next;
	}
}
