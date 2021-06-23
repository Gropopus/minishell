/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/23 13:40:51 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_print_tab_e(t_env *env, bool fork, int j)
{
	t_env	*s;

	if (!fork)
		return ;
	ft_list_sort(&env);
	s = env;
	while (s)
	{
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(s->var, 1);
		if (s->value)
		{
			ft_putstr_fd("=", 1);
			ft_putstr_fd("\"", 1);
			while (s->value[j])
			{
				if (s->value[j] == '"' || s->value[j] == '\\')
					ft_putstr_fd("\\", 1);
				ft_putchar_fd(s->value[j++], 1);
			}
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		s = s->next;
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
		ft_putstr_fd("export: not an identifier/invalid in this context", 2);
		if (name && *name)
		{
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd("\n", 2);
		}
	}
	return (1);
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
		ft_print_tab_e(env, fork, 0);
	else if (cmds->ac >= 3)
	{
		name = cmds->av[1];
		value = cmds->av[2];
	}
	else
	{
		name = ft_strdup(cmds->av[1]);
		while (name[i])
			if (name[i] == '=')
				name[i] = 0;
			else
				i++;
		if (cmds->av[1][i])
			value = name + i + 1;
	}
	return (do_export(name, value, env, fork));
}
