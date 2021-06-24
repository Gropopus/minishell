/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:03:28 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 19:44:44 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	builtin_manager(t_cmd *cmds, t_env *env, bool fork)
{
	int	ret;

	ret = 0;
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
		ret = ft_exec_exit(cmds, env, fork);
	else if (ft_strcmp(cmds->av[0], "export") == 0)
		ret = ft_exec_export(cmds, env, fork);
	return (ret);
}

int	start_child(t_cmd *cmds, t_env *env, bool builtin)
{
	if (!dup_pipes(&(cmds->pipe_open), cmds))
		exit(EXIT_FAILURE);
	if (builtin)
		exit(builtin_manager(cmds, env, true));
	if (!cmds->av[0])
		exit(ft_nice_error(9, cmds->av_cpy));
	if (cmds->is_piped)
		close(cmds->pipes[0]);
	if (execve(cmds->av[0], cmds->av, ft_env_to_my_env(env, 0, 0)) == -1)
	{
		if (errno == 13)
			ft_nice_error(2, cmds->av_cpy);
		else if (errno == 2)
			ft_nice_error(11, cmds->av_cpy);
		else
			ft_nice_error(7, cmds->av_cpy);
	}
	exit(EXIT_FAILURE);
}

int	exec_cmd(t_cmd *cmds, t_env *env, bool builtin)
{
	int		ret;

	cmds->pipe_open = 0;
	if (cmds->is_piped == 1 || (cmds->prev && cmds->prev->is_piped == 1))
	{
		cmds->pipe_open = 1;
		if (pipe(cmds->pipes))
			return (-1);
	}
	if (ft_redirection(cmds) != 0)
		return (0);
	ret = 0;
	disable_signals();
	cmds->pid = fork();
	if (cmds->pid == -1)
		return (ft_error(8));
	if (cmds->pid == 0)
		start_child(cmds, env, builtin);
	setup_signals();
	close_pipes(cmds->pipe_open, cmds);
	return (ret);
}

int	wait_exec(t_cmd *cmds, t_env *env)
{
	int	ret;
	int	status;

	while (cmds)
	{
		status = 0;
		waitpid(cmds->pid, &status, 0);
		if (WIFEXITED(status))
			ret = WEXITSTATUS(status);
		last_error(true, ret);
		if (cmds->path && cmds->path[0] == '\0')
			last_error(true, builtin_manager(cmds, env, false));
		cmds = cmds->next;
	}
	return (ret);
}

int	cmd_manager(t_cmd *cmds, t_env *env)
{
	int		ret;
	t_cmd	*list;

	list = cmds;
	ret = 0;
	while (cmds != NULL)
	{
		ret = ft_find_exec(cmds, env);
		if (ret != 0)
			return (ft_nice_error(ret, NULL));
		else
		{
			ret = exec_cmd(cmds, env, cmds->path && cmds->path[0] == '\0');
			if (cmds->av_cpy)
				free(cmds->av_cpy);
			cmds->av_cpy = NULL;
		}
		cmds = cmds->next;
	}
	cmds = list;
	ret = wait_exec(list, env);
	return (ret);
}
