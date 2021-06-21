/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/21 23:07:18 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_print_tab_d(char **t)
{
	int	i;
	int j;
	int f;

	i = 0;
	if (t == NULL || t[0] == NULL)
		return ;
	while (t[i] != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		j = -1;
		f = 0;
		while (++j < (int)ft_strlen(t[i]))
		{
			if (t[i][j] == '"' || t[i][j] == '\\')
				ft_putstr_fd("\\", 1);
			ft_putchar_fd(t[i][j], 1);
			if (!f && t[i][j] == '=')
			{
				ft_putstr_fd("\"", 1);
				f = 1;
			}
		}
		ft_putstr_fd("\"\n", 1);
		i++;
	}
}

int	ft_exec_export(t_cmd *cmds, t_env *env)
{
	(void)env;
	char **tabenv;

	if (cmds->ac < 2)
	{
		tabenv = ft_env_to_my_env(env, 0, 0);
		ft_sort_string_tab(tabenv);
		ft_print_tab_d(tabenv);
		ft_free_tab(tabenv);
		return (0);
	}
	//TODO
	return (0);
}
