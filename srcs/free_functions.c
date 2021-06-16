/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:42:59 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/16 14:16:12 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_free_cmd(t_cmd *cmds)
{
	if (cmds->line)
	{
		free(cmds->line);
		cmds->line = NULL;
	}
	if (cmds->av)
	{
		ft_free_tab(cmds->av);
		cmds->av = NULL;
	}
	if (cmds->my_env)
	{
		ft_free_tab(cmds->my_env);
		cmds->my_env = NULL;
	}
	if (cmds->path)
	{
		free(cmds->path);
		cmds->path = NULL;
	}
	cmds->ac = 0;
}

void	ft_free_env(t_env *env)
{
	t_env	*actual;
	t_env	*previous;

	actual = env;
	while (actual != NULL)
	{
		previous = actual;
		actual = actual->next;
		free(previous->var);
		previous->var = NULL;
		free(previous->value);
		previous->value = NULL;
		free(previous);
		previous = NULL;
	}
}
