/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:03:28 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/21 13:55:02 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	is_accessible(t_cmd *cmds)
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
}

int	builtin_manager(t_cmd *cmds, t_env *env)
{
	int	ret;

	ret = -1;
	if (ft_strcmp(cmds->av[0], "cd") == 0)
		ret = ft_exec_cd(cmds, env);
	else if (ft_strcmp(cmds->av[0], "echo") == 0)
		ret = ft_exec_echo(cmds, env);
	else if (ft_strcmp(cmds->av[0], "pwd") == 0)
		ret = ft_exec_pwd(cmds, env);
	else if (ft_strcmp(cmds->av[0], "env") == 0)
		ret = ft_exec_env(cmds, env);
	else if (ft_strcmp(cmds->av[0], "unset") == 0)
		ret = ft_exec_unset(cmds, env);
	else if (ft_strcmp(cmds->av[0], "exit") == 0)
		ft_exec_exit(cmds, env);
	else if (ft_strcmp(cmds->av[0], "export") == 0)
		ret = ft_exec_export(cmds, env);
	return (ret);
}

int dup_pipes(int *pipe_open, t_cmd *cmd)
{
	if (cmd->is_piped && dup2(cmd->pipes[1], 1) < 0)
		return (0);
	if (cmd->prev && cmd->prev->is_piped
		&& dup2(cmd->prev->pipes[0], 0) < 0)
		return (0);
	*pipe_open = 1;
	return (1);
}

int close_pipes(int pipe_open, t_cmd *cmd)
{
	if (pipe_open)
	{
		close(cmd->pipes[1]);
		if (!cmd->next)
			close(cmd->pipes[0]);
	}
	if (cmd->prev && cmd->prev->is_piped == 1)
		close(cmd->prev->pipes[0]);
	return (1);
}

int	exec_cmd(t_cmd *cmds, t_env *env, bool builtin)
{
	pid_t	pid;
	int		status;
	int		ret;
	int		pipe_open;

	status = 0;
	pipe_open = 0;


	if (!builtin)
	{
		ret = is_accessible(cmds);
		if (ret != 0)
			return (ret);
	}

	if (cmds->is_piped == 1 || (cmds->prev && cmds->prev->is_piped == 1))
	{
		pipe_open = 1;
		if (pipe(cmds->pipes))
			return (-1);
	}

	ret = 0;
	pid = fork();
	if (pid == -1)
		return (ft_error(8));
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);

		close_pipes(pipe_open, cmds);
		//if (WIFEXITED(status))
		//	ret = WEXITSTATUS(status);
	}
	else
	{
		if (!dup_pipes(&pipe_open, cmds))
			return (-1);
		if (builtin)
			exit(builtin_manager(cmds, env));
		if (execve(cmds->av[0], cmds->av, ft_env_to_my_env(env, 0, 0)) == -1)
			ft_error(7);
		exit(EXIT_FAILURE);
	}

	return (ret);
}

int	cmd_manager(t_cmd *cmds, t_env *env)
{
	int	ret;

	ret = 0;
	while (cmds != NULL)
	{
		if (cmds->av)
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
		}
		cmds = cmds->next;
	}
	return (ret);
}
