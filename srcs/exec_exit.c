/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 10:24:22 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 11:30:07 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

void			ft_exec_exit(t_cmd *cmds, t_env *env)
{
	int ret;

	ret = 1;
	if (cmds->ac > 2)
		ft_putstr_fd("exit: Too many arguments, extra arguments ignored\n", 2);
	if (cmds->ac >= 2)
	{
		if (ft_str_is_digit(cmds->av[1]) == 1)
			ret = ft_atoi(cmds->av[1]);
		else if (ft_str_is_digit(cmds->av[1]) == 0)
			ft_putstr_fd("exit: First argument is not a digit\n", 2);
	}
	else
		ret = 0;
	ft_free_cmd(cmds);
	ft_free_env(env);
	ft_printf("exit");
	exit(ret);
}
