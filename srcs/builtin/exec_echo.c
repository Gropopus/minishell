/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:43:07 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 15:57:04 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	ft_echo_av(t_cmd *cmds, int flag)
{
	int	i;

	i = 1;
	if (flag == 1)
		i = 2;
	while (cmds->av[i] && i < cmds->ac)
	{
		ft_printf("%s", cmds->av[i]);
		if (i + 1 < cmds->ac)
			ft_printf(" ");
		else if (i + 1 == cmds->ac && flag == 1)
			return (0);
		else if (i + 1 == cmds->ac && flag == 0)
		{
			ft_printf("\n");
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_exec_echo(t_cmd *cmds, t_env *env)
{
	int	flag;

	(void)env;
	flag = 0;
	if (cmds->ac < 2)
	{
		ft_printf("\n");
		return (0);
	}
	if (ft_strcmp(cmds->av[1], "-n") == 0)
		flag = 1;
	if (cmds->ac == 2 && flag == 1)
		return (0);
	else
		if ((ft_echo_av(cmds, flag)) < 0)
			return (1);
	return (0);
}
