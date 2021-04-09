/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:03:28 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 21:39:59 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

int		is_accessible(t_cmd *cmds)
{
	if (access(cmds->av[0], F_OK) != 0)
	{
		ft_printf("\n%s%sMyZsh$>%s", BOLD, CYAN, NC);
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(cmds->av_cpy, 2);
		ft_putstr_fd(": ", 2);
		free(cmds->av_cpy);
		cmds->av_cpy = NULL;
		return (ft_error(9));
	}
	else if (access(cmds->av[0], X_OK) != 0)
	{
		ft_printf("\n%s%sMyZsh$>%s", BOLD, CYAN, NC);
		ft_putchar_fd(' ', 2);
		ft_putstr_fd(cmds->av_cpy, 2);
		ft_putstr_fd(": ", 2);
		free(cmds->av_cpy);
		cmds->av_cpy = NULL;
		return (ft_error(2));
	}
	return (0);
}

int		exec_cmd(t_cmd *cmds)
{
	pid_t	pid;
	int		status;
	int		ret;

	status = 0;
	ret	= is_accessible(cmds);
	if (ret != 0)
		return (ret);
	pid = fork();
	if (pid == -1)
		return (ft_error(8));
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		if (execve(cmds->av[0], cmds->av, cmds->my_env) == -1)
			ft_error(7);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int			builtin_manager(t_cmd *cmds, t_env *env)
{
	int	ret;

//	ft_print_tab(cmds->my_env);
	ret = -1;
	if (ft_strcmp(cmds->av[0], "cd") == 0)
		ret = ft_exec_cd(cmds, env);
//	else if (ft_strcmp(cmds->av[0], "echo") == 0)
//		ret = ft_exec_echo(cmds, env);
	else if (ft_strcmp(cmds->av[0], "pwd") == 0)
		ret = ft_exec_pwd(cmds, env);
	else if (ft_strcmp(cmds->av[0], "env") == 0)
		ret = ft_exec_env(cmds, env);
	else if (ft_strcmp(cmds->av[0], "unset") == 0)
		ret = ft_exec_unset(cmds, env);
	else if (ft_strcmp(cmds->av[0], "exit") == 0)
		ft_exec_exit(cmds, env);
/*	else if (ft_strcmp(cmds->av[0], "export") == 0)
		ret = ft_exec_export(cmds, env);*/
	return (ret);
}

int			cmd_manager(t_cmd cmds, t_env *env)
{
	int ret;

	//les expansions a gerer ici ret = ft_expansions
	ret = ft_find_exec(&cmds, env);
	if (ret != 0)
	{
		ft_error(ret);
		return (1);
	}
	else
	{
		if (cmds.path[0] == '\0')
			builtin_manager(&cmds, env);
		else
			exec_cmd(&cmds);
	}
	ft_free_cmd(&cmds);
	return (ret);
}
