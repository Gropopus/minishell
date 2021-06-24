/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:05:15 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 19:10:58 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	add_arg(t_cmd *cmd, char *arg)
{
	int		c;
	int		i;
	char	**vnew;

	c = 0;
	while (cmd->av && cmd->av[c])
		c++;
	i = 0;
	vnew = malloc(sizeof(char *) * (c + 2));
	if (vnew == NULL)
		return ;
	while (i < c)
	{
		vnew[i] = cmd->av[i];
		i++;
	}
	vnew[i++] = arg;
	vnew[i] = NULL;
	if (cmd->av)
		free(cmd->av);
	cmd->av = vnew;
}

void	end_arg(char **a, enum e_redirect_type *type, t_cmd *cmd, bool *quote)
{
	if (*a && **a)
	{
		if (!type || *type == R_NONE)
			add_arg(cmd, *a);
		else
			add_redirection(cmd, *a, *type, quote);
		if (quote)
			*quote = false;
		*a = NULL;
		if (type)
			*type = R_NONE;
	}
}
