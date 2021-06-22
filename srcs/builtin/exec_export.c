/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/22 15:45:38 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_print_tab_e(t_env *env)
{
	t_env *s;
	int j;

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

bool is_valid_name(char *n)
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

int	ft_exec_export(t_cmd *cmds, t_env *env, bool fork)
{
	(void)env;
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	if (cmds->ac < 2)
	{
		if (fork)
		{
			ft_list_sort(&env);
			ft_print_tab_e(env);
		}
		return (0);
	}else if (cmds->ac >= 3){
		name = cmds->av[1];
		value = cmds->av[2];
	}else{
		int i = 0;
		name = ft_strdup(cmds->av[1]);
		while (name[i])
		{
			if (name[i] == '=')
				name[i] = 0;
			else
				i++;
		}
		if (cmds->av[1][i])
			value = name + i + 1;
	}


	if (name && is_valid_name(name))
	{
		env_manager(name, value, env);

		//tabenv = ft_env_to_my_env(env, 0, 0);
		/*if (!tabenv)
			return (ft_error(1));
		ft_sort_string_tab(tabenv);
		ft_print_tab_d(tabenv);
		ft_free_tab(tabenv);*/

	}else if (fork){
		printf("%s\n", "error");
	}

	//TODO
	return (0);
}
