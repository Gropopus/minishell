/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/20 19:08:34 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_print_tab_d(char **t)
{
	int	i;

	i = 0;
	if (t == NULL || t[0] == NULL)
		return ;
	while (t[i] != NULL)
	{
		ft_printf("declare -x %s\n", t[i]);
		i++;
	}
}

int	ft_exec_export(t_cmd *cmds, t_env *env)
{
	(void)env;

	if (cmds->ac < 2)
	{
		ft_print_tab_d(cmds->my_env);
		return (0);
	}
	//TODO
	return (0);
}
