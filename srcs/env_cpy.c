/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_cpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:25:01 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/20 11:25:37 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*ft_dup_to_equal(char *str,	char c)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	dest = malloc(sizeof(char) * i + 1);
	if (dest == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		dest[j] = str[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*ft_dup_pass_equal(char *str, char c)
{
	int		i;
	int		j;
	char	*dest;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == c)
			j = i + 1;
		i++;
	}
	dest = malloc(sizeof(char) * (i - j + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (str[j])
	{
		dest[i] = str[j];
		j++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

t_env	*ft_env_new(char *envp, unsigned int *error, int shlvl)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env) * 1);
	if (new == NULL)
		*error = 1;
	else
	{
		new->var = ft_dup_to_equal(envp, '=');
		new->value = ft_dup_pass_equal(envp, '=');
		if (new->var == NULL || new->value == NULL)
		{
			*error = 1;
			if (new->value)
				free(new->value);
			if (new->var)
				free(new->var);
			return (NULL);
		}
		if (ft_strcmp(new->var, "SHLVL") == 0)
		{
			shlvl = ft_atoi(new->value) + 1;
			free(new->value);
			new->value = ft_strdup(ft_itoa(shlvl));
		}
	}
	new->next = NULL;
	return (new);
}

t_env	*init_empty_env(unsigned int *error)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env) * 1);
	if (new == NULL)
	{
		*error = 1;
		return (NULL);
	}
	new->var = ft_strdup("PWD");
	new->value = getcwd(NULL, 0);
	if (new->var == NULL || new->value == NULL)
	{
		*error = 1;
		if (new->value)
			free(new->value);
		if (new->var)
			free(new->var);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_env	*ft_env_cpy(unsigned int *error, char **envp)
{
	int		i;
	t_env	*env;
	t_env	*actual;

	if (!envp || !envp[0])
	{
		env = init_empty_env(error);
		return (env);
	}
	actual = ft_env_new(envp[0], error, 0);
	if (actual == NULL)
		return (NULL);
	env = actual;
	i = 1;
	while (envp[i])
	{
		actual->next = ft_env_new(envp[i], error, 0);
		actual = actual->next;
		if (actual == NULL)
			return (NULL);
		i++;
	}
	return (env);
}
