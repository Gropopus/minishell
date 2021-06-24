/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:10:36 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 22:53:47 by ttranche         ###   ########.fr       */
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
		if (f->type && f->type != R_NONE && f->type != RR_INPUT)
			close(f->fd);
		f = f->next;
	}
}

void	ft_heredoc(t_file_list *f, t_env *env)
{
	char *line;
	char *temp;

	pipe(f->pipes);
	while (1)
	{
		line = readline("> ");
		if (!line)
			continue ;
		if (ft_strcmp(line, f->path) == 0)
		{
			free(line);
			break ;
		}
		if (!f->quote)
		{
			temp = line;
			line = fill_vars(line, env, 0, NULL);
			free(temp);
		}
		write(f->pipes[1], line, ft_strlen(line));
		write(f->pipes[1], "\n", 1);
 		free(line);
	}
	close(f->pipes[1]);
}

int	ft_input(t_cmd *cmd, t_env *env)
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
		}
		else if (f->type == RR_INPUT)
		{
			ft_heredoc(f, env);
		}
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
		}
		else if (f->type == RR_OUTPUT)
		{
			f->fd = open(f->path, O_CREAT | O_RDWR | O_APPEND, 0644);
			if (errno == EACCES)
				return (ft_error(2));
		}
		f = f->next;
	}
	return (0);
}

int	ft_redirection(t_cmd *cmd, t_env *env)
{
	if (ft_input(cmd, env) != 0)
		return (-1);
	if (ft_output(cmd) != 0)
		return (-1);
	return (0);
}
