/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 16:42:51 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/16 14:45:50 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	ft_exec_pwd(t_cmd *cmds, t_env *env)
{
	char	*path;

	(void)cmds;
	path = ft_env_chr(env, "PWD");
	if (path == NULL)
		return (ft_error(4));
	ft_printf("%s\n", path);
	return (0);
}
