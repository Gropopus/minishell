/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:55:01 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 16:39:41 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

int		ft_add_to_env(char *var, char *value, t_env *env)
{
	t_env *new;
	t_env *actual;

	actual = env;
	if (!actual)
		return (ft_error(5));
	if (ft_strcmp(env->var, "") == 0 && ft_strcmp(env->value, "") == 0)
	{
		free(env->var);
		free(env->value);
		if (((env->var = ft_strdup(var)) == NULL)
			|| ((env->value = ft_strdup(value)) == NULL))
			return (ft_error(1));
		return (0);
	}
	if ((new = malloc(sizeof(t_env) * 1)) == NULL)
		return (ft_error(1));
	if (((new->var = ft_strdup(var)) == NULL)
		|| ((new->value = ft_strdup(value)) == NULL))
		return (ft_error(1));
	while (actual->next)
		actual = actual->next;
	actual->next = new;
	return (0);
}

int		env_manager(char *var, char *value, t_env *env)
{
	t_env	*actual;

	actual = env;
	while (actual != NULL)
	{
		if (ft_strcmp(actual->var, var) == 0)
		{
			free(actual->value);
			if ((actual->value = ft_strdup(value)) == NULL)
				return (ft_error(1));
			return (0);
		}
		actual = actual->next;
	}
	if ((ft_add_to_env(var, value, env)) != 0)
		return (-1);
	return (0);
}
