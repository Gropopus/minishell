/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:10:36 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/22 18:48:02 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

void	ft_close_fd(t_cmd *cmd)
{
	t_file_list	*f;

	f = cmd->file;
	while (f)
	{
		if (f->type && f->type != R_NONE)
			close(f->fd);
		f = f->next;
	}
}

int	ft_input(t_cmd *cmd)
{
	t_file_list	*f;

	f = cmd->file;
	while (f)
	{
		if (f->type == R_INPUT)
		{
			f->fd = open(f->path, O_RDONLY);
			if (errno == EACCES)
			{
				return (ft_error(2));
			}
			else if (f->fd < 0)
			{
				ft_putstr_fd(" no such file or directory: ", 2);
				return (1);
			}
			dup2(f->fd, 0);
		}
/*		else if (f->type == RR_INPUT)
		{
			f->fd = open(f->path, O_RDONLY);
			if (errno == EACCES)
				return (ft_error(2));
			else if (f->fd < 0)
			{
				ft_putstr_fd(" no such file or directory: ", 2);
				return (1);
			}
			dup2(f->fd, 0);
		}*/
		f = f->next;
	}
	return (0);
}

int	ft_output(t_cmd *cmd)
{
	t_file_list	*f;

	f = cmd->file;
	while (f)
	{
		if (f->type == R_OUTPUT)
		{
			f->fd = open(f->path, O_RDWR | O_CREAT | O_TRUNC, 0666);
			if (errno == EACCES)
				return (ft_error(2));
			dup2(f->fd, 1);
		}
		else if (f->type == RR_OUTPUT)
		{
			f->fd = open(f->path, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (errno == EACCES)
				return (ft_error(2));
			dup2(f->fd, 1);
		}
		f = f->next;
	}
	return (0);
}

int	ft_redirection(t_cmd *cmd)
{
	if (ft_input(cmd) != 0)
		return (-1);
	else if (ft_output(cmd) != 0)
		return (-1);
	return (0);
}
