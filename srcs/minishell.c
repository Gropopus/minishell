/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/21 21:49:32 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"
#include "../includes/minishell.h"

int	is_in_builtin(char **cmds)
{
	int	yes;
	int	i;

	yes = 0;
	i = 0;
	while (cmds && cmds[i])
	{
		if (ft_strcmp(cmds[i], "cd") == 0 || ft_strcmp(cmds[i], "echo") == 0
			|| ft_strcmp(cmds[i], "pwd") == 0
			|| ft_strcmp(cmds[i], "env") == 0
			|| ft_strcmp(cmds[i], "exit") == 0
			|| ft_strcmp(cmds[i], "unset") == 0
			|| ft_strcmp(cmds[i], "export") == 0)
			yes++;
		i++;
	}
	if (yes > 0)
		return (1);
	else
		return (0);
}

int	ft_minishell(t_env *env, int ret)
{
	t_cmd	*cmds;
	char	*line;

	while (1)
	{
		line = readline(CYAN BOLD "🖥  Minishell $> "NC);
		if (line)
		{
			cmds = parse(line, env);
			ft_fill_cmds(cmds, env);
			//if (ret == 0)
			ret = cmd_manager(cmds, env);
			//if (ret != 0)
			//	ft_error(ret);
		}
		if (line)
		{
			add_history(line);
			free(line);
		}
		else
		{
			ft_putstr_fd("\b\bexit\n", 1);
			return (0);
		}
	}
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	unsigned int	error;
	t_env			*env;

	(void)ac;
	(void)av;
	env = ft_env_cpy(&error, envp);
	if (env == NULL)
		return (ft_error(error));
	return (ft_minishell(env, 0));
}
