/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expansion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 11:39:39 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 12:01:56 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

int			ft_dollar_expansion(t_env *env, char **av)
{
	int i;
	int ret;
	int tmp;
	char	*start;

	i = 0;
	ret = 0;
	while(av[i])
	{
		start = ft_strchr(av[i], '$');
		if (av[i][0] == '~' || start != NULL)
		{
			tmp = ft_replace_by_var(&av[i], env);
			if (tmp != 0)
				ret = tmp;
		}
		i++;
	}
	return (ret);
}
