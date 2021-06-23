/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
<<<<<<< Updated upstream
/*   Updated: 2021/06/22 19:04:18 by thsembel         ###   ########.fr       */
=======
/*   Updated: 2021/06/22 18:37:16 by ttranche         ###   ########.fr       */
>>>>>>> Stashed changes
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

<<<<<<< Updated upstream
void	ft_print_tab_e(t_env *env, bool fork, int j)
=======
void	ft_print_tab_e(t_env *env, bool fork)
>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
int	do_export(char *name, char *value, t_env *env, bool fork)
=======
int do_export(char *name, char *value, t_env *env, bool fork)
>>>>>>> Stashed changes
{
	if (name == NULL && value == NULL)
		return (0);
	if (name && is_valid_name(name) == 1)
	{
		env_manager(name, value, env);
		return (0);
	}
<<<<<<< Updated upstream
	if (fork)
	{
=======
	if (fork){
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
	char	*name;
	int		i;
	char	*value;
=======
	char *name;
	int i;
	char *value;
>>>>>>> Stashed changes

	name = NULL;
	value = NULL;
	i = 0;
	if (cmds->ac < 2)
<<<<<<< Updated upstream
		ft_print_tab_e(env, fork, 0);
	else if (cmds->ac >= 3)
	{
=======
		ft_print_tab_e(env, fork);
	else if (cmds->ac >= 3){
>>>>>>> Stashed changes
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
