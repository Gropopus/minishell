/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/25 01:47:54 by ttranche         ###   ########.fr       */
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

char	*get_prompt(t_env *env)
{
	char	*prompt;
	char	*name;
	char	*bef;
	char	*mid;
	char	*aft;

	name = ft_env_chr(env, "USER");
	bef = "🖥  " PURPLE "@";
	mid = NC " ~ ";
	aft = CYAN BOLD"Minishell $> " NC;
	if (!name)
		name = "bash";
	prompt = malloc(1 + ft_strlen(bef)
			+ ft_strlen(name) + ft_strlen(mid) + ft_strlen(aft));
	if (!prompt)
		return ("$> ");
	prompt[0] = 0;
	ft_strcat(prompt, bef);
	ft_strcat(prompt, name);
	ft_strcat(prompt, mid);
	ft_strcat(prompt, aft);
	return (prompt);
}

void	ft_add_history(char *line)
{
	if (line && *line)
		add_history(line);
}

int	ft_minishell(t_env *env, int ret, t_cmd	*cmds, char	*line)
{
	char	*prompt;

	while (1)
	{
		prompt = get_prompt(env);
		line = readline(prompt);
		free(prompt);
		if (line)
		{
			cmds = parse(line, env);
			ft_fill_cmds(cmds, env);
			cmd_manager(cmds, env);
			ft_free_cmd(cmds);
		}
		ft_add_history(line);
		if (!line)
		{
			ft_putstr_fd("\b\bexit\n", 1);
			ft_free_env(env);
			//while (1);
			return (0);
		}
		if (line)
			free(line);
	}
	return (ret);
}

int	main(int ac, char **av, char **envp)
{
	unsigned int	error;
	t_env			*env;

	(void)ac;
	(void)av;
	if (!setup_signals())
		return (ft_nice_error(0, NULL));
	env = ft_env_cpy(&error, envp);
	if (env == NULL)
		return (ft_nice_error(1, NULL));
	return (ft_minishell(env, 0, NULL, NULL));
}
