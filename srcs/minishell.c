/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/08 23:56:09 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include "../includes/minishell.h"

int			is_in_builtin(char **cmds)
{
	int yes;
	int i;

	yes = 0;
	i = 0;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "cd") == 0 || ft_strcmp(cmds[i], "echo") == 0 ||
			ft_strcmp(cmds[i], "pwd") == 0 || ft_strcmp(cmds[i], "env") == 0 ||
			ft_strcmp(cmds[i], "exit") == 0 ||ft_strcmp(cmds[i], "unset") == 0
			|| ft_strcmp(cmds[i], "export") == 0)
			yes++;
		i++;
	}
	if (yes > 0)
		return (1);
	else
		return (0);
}

/*static int	input_loop(t_env *env_start)
{
	t_command	command;
	int			ret;

	while (1)
	{
		ft_printf(SHELL_PROMPT);
		command.input = NULL;
		command.path = NULL;
		if (get_next_line(0, &(command.input)) == 0)
		{
			ret = ft_getstatus(env_start);
			ft_free_env_list(env_start);
			free(command.input);
			return (ret);
		}
		if (command.input[0] != '\0')
		{
			ret = ft_split_command(env_start, &command);
			if (ret == 0)
				ret = ft_handle_command(env_start, command);
		}
		else
			free(command.input);
	}
	return (ret);
}*/

int		ft_minishell(t_env *env)
{
	t_cmd	cmds;
	int		ret;

	ret = 0;
	while (1)
	{
		ft_printf("%s%sMyZsh$>%s", BOLD, CYAN, NC);
		cmds.path = NULL;
		if (get_next_line(0, &cmds.line) == 0)
		{
			ft_free_env(env);
			free(cmds.line);
			return (ret);
		}
		else if (cmds.line[0])
		{
			ret = ft_fill_cmds(&cmds, env);
			if (ret == 0)
				ret = cmd_manager(cmds, env);
			if (ret != 0)
				ft_error(ret);
		}
		else
			free(cmds.line);
	}
	return (ret);
}

int		main(int ac, char **av, char **envp)
{
	unsigned int	error;
	t_env			*env;
	(void)ac;
	(void)av;
	if ((env = ft_env_cpy(&error, envp)) == NULL)
		return (ft_error(error));
	while (env->next)
	{
		printf("%s=%s\n", env->var, env->value);
		env= env->next;
	}
	return (ft_minishell(env));
}

