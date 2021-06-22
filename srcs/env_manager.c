/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:55:01 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/22 15:24:54 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

t_env	*ft_add_to_env_bis(char *var, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env) * 1);
	if (new == NULL)
		return (NULL);
	new->var = ft_strdup(var);
	new->value = ft_strdup(value);
	new->next = NULL;
	if (value && new->value == NULL)
		return (NULL);
	if (new->var == NULL)
		return (NULL);
	return (new);
}

int	ft_add_to_env(char *var, char *value, t_env *env)
{
	t_env	*new;
	t_env	*actual;

	actual = env;
	if (!actual)
		return (ft_error(5));
	if (ft_strcmp(env->var, "") == 0 && ft_strcmp(env->value, "") == 0)
	{
		free(env->var);
		free(env->value);
		env->var = ft_strdup(var);
		env->value = ft_strdup(value);
		if (env->var == NULL || (value && env->value == NULL))
			return (ft_error(1));
		return (0);
	}
	new = ft_add_to_env_bis(var, value);
	if (new == NULL)
		return (ft_error(1));
	while (actual->next)
		actual = actual->next;
	actual->next = new;
	return (0);
}

int	env_manager(char *var, char *value, t_env *env)
{
	t_env	*actual;

	actual = env;
	while (actual != NULL)
	{
		if (ft_strcmp(actual->var, var) == 0)
		{
			if (!value)
				return (0);
			free(actual->value);
			actual->value = ft_strdup(value);
			if (actual->value == NULL && value)
				return (ft_error(1));
			return (0);
		}
		actual = actual->next;
	}
	if ((ft_add_to_env(var, value, env)) != 0)
		return (-1);
	return (0);
}
