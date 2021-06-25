/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:42:59 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/25 01:59:25 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_free_cmd_stuff(t_cmd *cmds) {
	int	i;
	t_file_list *next;

	i = 0;
	if (cmds->av_cpy)
		free(cmds->av_cpy);
	cmds->av_cpy = NULL;
	if (cmds->path)
		free(cmds->path);
	cmds->path = NULL;
	if (cmds->av)
	{
		while (i < cmds->ac)
			free(cmds->av[i++]);
		free(cmds->av);
		cmds->av = NULL;
	}
	while (cmds->file)
	{
		next = cmds->file->next;
		if (cmds->file->path)
			free(cmds->file->path);
		free(cmds->file);
		cmds->file = next;
	}
}

void	ft_free_cmd(t_cmd *cmds)
{
	t_cmd *next;

	while (cmds && cmds->prev != NULL)
		cmds = cmds->prev;
	while (cmds)
	{
		next = cmds->next;
		ft_free_cmd_stuff(cmds);
		cmds->ac = 0;
		free(cmds);
		cmds = next;
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
	free(last_error(false, 0));
}
