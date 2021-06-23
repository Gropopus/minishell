/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:03:28 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/23 17:44:33 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*int	is_accessible(t_cmd *cmds)
{
	int ret;

	ret = 0;
	if (!cmds->path)
		ret = (ft_nice_error(9, NULL));
	else if (access(cmds->av[0], F_OK) != 0)
		ret = (ft_nice_error(9, cmds->av_cpy));
	else if (access(cmds->av[0], X_OK) != 0)
		ret = (ft_nice_error(2, cmds->av_cpy));
	if (cmds->av_cpy)
		free(cmds->av_cpy);
	cmds->av_cpy = NULL;
	return (ret);
}*/


int	is_accessible(t_cmd *cmds)
{
	int			ret;
	int			fd;


	fd = open(cmds->av[0], O_RDWR);
	ret = 0;
	if (!cmds->path)
		ret = (ft_nice_error(9, NULL));
	else if (chdir(cmds->av[0]) == 0)
		ret = (ft_nice_error(2, cmds->av_cpy));
	if (cmds->av_cpy)
		free(cmds->av_cpy);
	cmds->av_cpy = NULL;
	if (fd >= 0)
		close(fd);
	return (ret);
}

int	builtin_manager(t_cmd *cmds, t_env *env, bool fork)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(cmds->av[0], "cd") == 0)
		ret = ft_exec_cd(cmds, env, fork);
	else if (fork && ft_strcmp(cmds->av[0], "echo") == 0)
		ret = ft_exec_echo(cmds, env);
	else if (fork && ft_strcmp(cmds->av[0], "pwd") == 0)
		ret = ft_exec_pwd(cmds, env);
	else if (fork && ft_strcmp(cmds->av[0], "env") == 0)
		ret = ft_exec_env(cmds, env);
	else if (ft_strcmp(cmds->av[0], "unset") == 0)
		ret = ft_exec_unset(cmds, env, fork);
	else if (ft_strcmp(cmds->av[0], "exit") == 0)
		ft_exec_exit(cmds, env, fork);
	else if (ft_strcmp(cmds->av[0], "export") == 0)
		ret = ft_exec_export(cmds, env, fork);
	return (ret);
}

int dup_pipes(int *pipe_open, t_cmd *cmd)
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

int close_pipes(int pipe_open, t_cmd *cmd)
{
	if (pipe_open)
	{
		close(cmd->pipes[1]);
		if (!cmd->next)
		{
			close(cmd->pipes[0]);
		}
	}
	if (cmd->prev && cmd->prev->is_piped == 1)
	{
		close(cmd->prev->pipes[0]);
	}
	return (1);
}

int	exec_cmd(t_cmd *cmds, t_env *env, bool builtin)
{
	int		ret;

	cmds->pipe_open = 0;

	if (!builtin && cmds->av)
	{
		ret = is_accessible(cmds);
		if (ret != 0)
			return (ret);
	}
	if (cmds->is_piped == 1 || (cmds->prev && cmds->prev->is_piped == 1))
	{
		cmds->pipe_open = 1;
		if (pipe(cmds->pipes))
			return (-1);
	}
	if (ft_redirection(cmds) != 0)
		return (0);
	ret = 0;
	cmds->pid = fork();
	if (cmds->pid == -1)
		return (ft_error(8));
	if (cmds->pid == 0)
	{
		if (!dup_pipes(&(cmds->pipe_open), cmds))
			return (-1);
		if (builtin)
			exit(builtin_manager(cmds, env, true));
		if (!cmds->av[0])
			return (-1);
		close(cmds->pipes[0]);
		if (execve(cmds->av[0], cmds->av, ft_env_to_my_env(env, 0, 0)) == -1)
			ft_error(9);
		exit(EXIT_FAILURE);
	}
	close_pipes(cmds->pipe_open, cmds);
	return (ret);
}

int	cmd_manager(t_cmd *cmds, t_env *env)
{
	int	ret;
	int		status;
	t_cmd	*list;

	list = cmds;
	ret = 0;
	while (cmds != NULL)
	{
			ret = ft_find_exec(cmds, env);
			if (ret != 0)
			{
				ft_error(ret);
				return (1);
			}
			else
			{
				ret = exec_cmd(cmds, env, cmds->path && cmds->path[0] == '\0');
			}
		cmds = cmds->next;
	}
	cmds = list;
	while (cmds)
	{
		status = 0;
		waitpid(cmds->pid, &status, 0);
		if (cmds->path && cmds->path[0] == '\0')
			builtin_manager(cmds, env, false);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		cmds = cmds->next;
	}
	return (ret);
}
