/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:24:22 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 16:09:10 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	ft_exec_exit(t_cmd *cmds, t_env *env, bool fork)
{
	int	ret;

	if (cmds && cmds->ac > 2 && fork)
	{
		ft_putstr_fd("exit: Too many arguments, extra arguments ignored\n", 2);
		return (1);
	}
	if (cmds && cmds->ac >= 2)
	{
		if (ft_str_is_digit(cmds->av[1]) == 1)
			ret = ft_atoi(cmds->av[1]);
		else if (ft_str_is_digit(cmds->av[1]) == 0)
		{
			if (fork)
				ft_putstr_fd("exit: First argument is not a digit\n", 2);
			return (1);
		}
	}
	if (fork)
		ft_printf("exit\n");
	ft_free_cmd(cmds);
	ft_free_env(env);
	exit(0);
	return (1);
}
