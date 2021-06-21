/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 18:05:49 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/21 23:14:37 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	ft_exec_env(t_cmd *cmds, t_env *env)
{
	char **tabenv;

	(void)cmds;
	if (env)
	{
		tabenv = ft_env_to_my_env(env, 0, 0);
		ft_print_tab(tabenv);
		ft_free_tab(tabenv);
		return (0);
	}
	else
		return (ft_error(5));
}
