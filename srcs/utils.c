/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:19:51 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/16 14:35:18 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/ft_printf.h"
#include "../includes/minishell.h"

int	ft_env_str_len(char *string)
{
	int	i;

	i = 0;
	while (string[i] == '_' || (string[i] >= 'A' && string[i] <= 'Z')
		|| (string[i] >= 'a' && string[i] <= 'z')
		|| (string[i] >= '0' && string[i] <= '9'))
	{
		i++;
	}
	return (i);
}

void	ft_strexpand(char **source, const char *addition)
{
	void	*temp;

	temp = *source;
	if (*source == NULL)
		*source = ft_strdup(addition);
	else if (addition != NULL)
	{
		*source = ft_strjoin(*source, addition);
		free(temp);
	}
}

void	ft_str_expand_triple(char **src, char *add1, char *add2)
{
	ft_strexpand(src, add1);
	if (*src == NULL)
		return ;
	ft_strexpand(src, add2);
}
