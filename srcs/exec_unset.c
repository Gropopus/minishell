/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 21:41:50 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 22:14:13 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

int	remove_if_isfirst(t_env *first)
{
	t_env *second;

	if (first->next == NULL)
	{
		free(first->var);
		free(first->value);
		first->var = ft_strdup("");
		first->value = ft_strdup("");
		if (first->var == NULL || first->value == NULL)
			return (ft_error(1));
	}
	else
	{
		second = first->next;
		free(first->var);
		first->var = second->var;
		free(first->value);
		first->value = second->value;
		first->next = second->next;
		free(second);
	}
	return (0);
}

int			unset_env(char *var, t_env *env)
{
	t_env	*actual;
	t_env	*previous;

	previous = env;
	if (env == NULL)
		return (ft_error(5));
	if (ft_strcmp(previous->var, var) == 0)
	{
		remove_if_isfirst(previous);
		return (0);
	}
	while (previous != NULL)
	{
		if (previous->next != NULL &&
			ft_strcmp((previous->next)->var, var) == 0)
			break ;
		previous = previous->next;
	}
	if (previous == NULL)
		return (ft_error(4));
	actual = previous->next;
	free(actual->var);
	free(actual->value);
	previous->next = actual->next;
	free(actual);
	return (0);
}

int			ft_exec_unset(t_cmd *cmds, t_env *env)
{
	int	i;
	int	ret;

	i = 1;
	if (cmds->ac >= 2)
	{
		while (cmds->av[i] && i < cmds->ac)
		{
			unset_env(cmds->av[i], env);
			i++;
		}
		ret = 0;
	}
	else
	{
		ft_putstr_fd("unset : Not enough arguments.\n", 2);
		ret = 1;
	}
//	ft_setstatus(env_list, ret);
	return (ret);
}
