/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:42:59 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/21 23:09:09 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_free_cmd(t_cmd *cmds)
{
	while (cmds->next != NULL)
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
		/*if (cmds->my_env)
		{
			ft_free_tab(cmds->my_env);
			cmds->my_env = NULL;
		}*/
		if (cmds->path)
		{
			free(cmds->path);
			cmds->path = NULL;
		}
		cmds->ac = 0;
		cmds = cmds->next;
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*actual;
	t_env	*next;

	actual = env;
	while (actual != NULL)
	{
		next = actual->next;
		free(actual->var);
		actual->var = NULL;
		free(actual->value);
		actual->value = NULL;
		free(actual);
		actual = next;
	}
}
