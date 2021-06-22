/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 15:19:51 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/22 15:40:47 by ttranche         ###   ########.fr       */
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

void	ft_swap_list(t_env **prevnext, t_env *last)
{
	t_env	*swap;

	swap = *prevnext;
	*prevnext = last->next;
	swap->next = last->next->next;
	(*prevnext)->next = swap;
}

void	ft_list_sort(t_env **begin_list)
{
	t_env	*last;
	t_env	*prev;

	prev = NULL;
	last = *begin_list;
	while (last && last->next)
	{
		if (ft_strcmp(last->var, last->next->var) > 0)
		{
			if (prev == NULL)
				ft_swap_list(begin_list, last);
			else
				ft_swap_list(&(prev->next), last);
			last = *begin_list;
			prev = NULL;
		}
		else
		{
			prev = last;
			last = last->next;
		}
	}
}
