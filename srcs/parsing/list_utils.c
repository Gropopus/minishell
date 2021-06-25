/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:03:24 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/25 02:34:48 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

t_cmd	*blank_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->av = NULL;
	cmd->ac = 0;
	cmd->is_piped = false;
	cmd->file = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	cmd->path = NULL;
	cmd->av_cpy = NULL;
	return (cmd);
}

void	ft_free_list(t_file_list **list)
{
	t_file_list	*l;
	t_file_list	*next;

	l = *list;
	while (l)
	{
		next = l->next;
		free(l);
		l = next;
	}
	*list = NULL;
}

t_cmd	*error_clean(t_cmd *list, char *r, char n)
{
	int	i;
	t_cmd *next;

	if (r)
		free(r);
	while (list)
	{
		next = list->next;
		i = 0;
		while (list->av && list->av[i])
			free(list->av[i++]);
		free(list->av);
		ft_free_list(&list->file);
		free(list);
		list = next;
	}
	ft_syntax_error(n);
	return (NULL);
}

void	next_cmd(t_cmd **cur, bool piped)
{
	t_cmd	*temp;

	temp = *cur;
	if (piped)
		(*cur)->is_piped = piped;
	(*cur)->next = blank_cmd();
	*cur = (*cur)->next;
	(*cur)->prev = temp;
}

void	add_redirection(t_cmd *cmd, char *arg,
			enum e_redirect_type type, bool *quote)
{
	t_file_list	*new;
	t_file_list	*c;

	new = malloc(sizeof(t_file_list));
	if (new == NULL)
		return ;
	new->path = arg;
	new->type = type;
	new->next = NULL;
	if (quote)
		new->quote = *quote;
	else
		new->quote = false;
	if (!cmd->file)
		cmd->file = new;
	else
	{
		c = cmd->file;
		while (c->next)
			c = c->next;
		c->next = new;
	}
}
