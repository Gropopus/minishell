/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 19:40:36 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_print_tab_e(t_env *env, bool fork, int j)
{
	if (!fork)
		return ;
	ft_list_sort(&env);
	while (env)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(env->var, 1);
		if (env->value)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			while (env->value[j])
			{
				if (env->value[j] == '"' || env->value[j] == '\\')
					ft_putstr_fd("\\", 1);
				ft_putchar_fd(env->value[j++], 1);
			}
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}

bool	is_valid_name(char *n)
{
	if (!n)
		return (false);
	if (ft_isdigit(*n))
		return (false);
	while (*n)
	{
		if (!ft_isalnum(*n) && *n != '_')
			return (false);
		n++;
	}
	return (true);
}

int	do_export(char *name, char *value, t_env *env, bool fork)
{
	if (name == NULL && value == NULL)
		return (0);
	if (name && is_valid_name(name) == 1)
	{
		env_manager(name, value, env);
		return (0);
	}
	if (fork)
	{
		ft_putstr_fd("export: not a valid identifier"
			"/invalid in this context", 2);
		if (name && *name)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return (1);
}

int	export(t_cmd *cmds, t_env *env, bool fork)
{
	char	*name;
	char	*value;
	int		i;
	int		j;

	i = 1;
	while (i < cmds->ac)
	{
		name = NULL;
		value = NULL;
		name = ft_strdup(cmds->av[i]);
		j = 0;
		while (name[j])
		{
			if (name[j] == '=')
				name[j] = 0;
			else
				j++;
		}
		if (cmds->av[i][j])
			value = name + j + 1;
		do_export(name, value, env, fork);
		i++;
	}
	return (0);
}

int	ft_exec_export(t_cmd *cmds, t_env *env, bool fork)
{
	char	*name;
	int		i;
	char	*value;

	name = NULL;
	value = NULL;
	i = 0;
	if (cmds->ac < 2)
	{
		ft_print_tab_e(env, fork, 0);
		return (0);
	}
	return (export(cmds, env, fork));
}
