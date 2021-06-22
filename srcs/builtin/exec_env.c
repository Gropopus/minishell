/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/22 15:45:34 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_print_tab_ev(t_env *env)
{
	t_env *s;
	int j;

	s = env;
	while (s)
	{
		j = 0;
		if (s->value)
		{
			ft_putstr_fd(s->var, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(s->value, 1);
		}
		ft_putchar_fd('\n', 1);
		s = s->next;
	}
}

int	ft_exec_env(t_cmd *cmds, t_env *env)
{
	(void)cmds;
	if (env)
	{
		ft_print_tab_ev(env);
		return (0);
	}
	else
		return (ft_error(5));
}
