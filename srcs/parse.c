/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:59:40 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/23 14:38:23 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/ft_printf.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

char	*get_arg(char *name, t_env *env)
{
	char *path;

	path = ft_env_chr(env, name);
	if (path == NULL)
		return ("");
	return (path);
}

char	*ft_strnewcat(char *s, char *o, int len)
{
	int		i;
	int		j;
	char	*n;

	n = malloc(ft_strlen(s) + len + 2);
	if (n == NULL)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		n[i] = s[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		n[i + j] = o[j];
		j++;
	}
	n[i + j] = 0;
	if (s)
		free(s);
	return (n);
}

bool	is_alpha_num(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
}

char	*extract_var_name(char *parse, int *cur)
{
	char	*read;
	int		i;

	read = malloc(1);
	if (read == NULL)
		return (NULL);
	read[0] = 0;
	i = 1;
	if (parse[i] == '?')
	{
		*cur += 2;
		return (ft_strnewcat(read, "?", 1));
	}
	while (parse[i])
	{
		if (!is_alpha_num(parse[i]))
		{
			*cur += i;
			return (read);
		}
		read = ft_strnewcat(read, parse + i++, 1);
	}
	*cur += i;
	return (read);
}

int	read_marks_2(char mark, char *parse, int *i, int *cur)
{
	if (parse[*i] == mark)
	{
		*cur += *i + 1;
			return (0);
	}
	if (mark == '"' && parse[*i] == '\\' && (parse[*i + 1] == '\\'
			|| parse[*i + 1] == mark || parse[*i + 1] == '$'))
		*i += 1;
	return (1);
}

char	*read_marks(char *parse, int *cur, char mark, t_env *env)
{
	char	*read;
	int		t;
	char	*name;
	char	*value;
	int i;

	i = 1;
	read = malloc(1);
	if (read == NULL)
		return (NULL);
	read[0] = 0;
	while (parse[i])
	{
		if (read_marks_2(mark, parse, &i, cur) == 0)
			return (read);
		else if (mark == '"' && parse[i] == '$')
		{
			t = 0;
			name = extract_var_name(parse + i, &t);
			if (ft_strlen(name) > 0)
			{
				i += t;
				value = get_arg(name, env);
				free(name);
				read = ft_strnewcat(read, value, ft_strlen(value));
				continue ;
			}
			free(name);
		}
		read = ft_strnewcat(read, parse + i++, 1);
	}
	free(read);
	read = NULL;
	return (read);
}

bool	ft_starts_with(char *s, char *sta)
{
	while (*sta)
	{
		if (!*s)
			return (false);
		if (*s != *sta)
			return (false);
		++sta;
		++s;
	}
	return (true);
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

	if (r)
		free(r);
	while (list)
	{
		i = 0;
		while (list->av && list->av[i])
			free(list->av[i++]);
		free(list->av);
		ft_free_list(&list->file);
		list = list->next;
	}
	ft_syntax_error(n);
	return (NULL);
}

t_cmd	*blank_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->av = NULL;
	cmd->is_piped = false;
	cmd->file = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int		c;
	int		i;
	char	**vnew;

	c = 0;
	while (cmd->av && cmd->av[c])
		c++;
	i = 0;
	vnew = malloc(sizeof(char*) * (c + 2));
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

void	add_redirection(t_cmd *cmd, char *arg, enum e_redirect_type type, bool *quote)
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

void	next_cmd(t_cmd **cur, bool piped)
{
	t_cmd *temp;

	temp = *cur;
	if (piped)
		(*cur)->is_piped = piped;
	(*cur)->next = blank_cmd();
	*cur = (*cur)->next;
	(*cur)->prev = temp;
}

/*
http://www.compciv.org/topics/bash/variables-and-substitution/
Variable names can contain a sequence of alphanumeric characters and underscores. For variables created by you, the user, they should start with either an alphabetical letter or an underscore (i.e. not a number):

*/


void	printf_cmds(t_cmd *cur)
{
	int		i;
	char	*rt;

	i = 0;
	while (cur)
	{
		printf(" -------- \n");
		printf(" Piped: %s\n", cur->is_piped ? "YES" : "NO");

		i = 0;
		while (cur->av && cur->av[i])
		{
			printf("ARG[%i]: %s\n", i, cur->av[i]);
			i++;
		}
		t_file_list *c = cur->file;
		while (c)
		{
			rt = "Unk";
			if (c->type == R_INPUT)
				rt = "<";
			if (c->type == RR_INPUT)
				rt = "<<";
			if (c->type == R_OUTPUT)
				rt = ">";
			else if (c->type == RR_OUTPUT)
				rt = ">>";
			printf("REDIR(%s): %s Escaped: %s\n", rt, c->path, c->quote ? "true" : "false");
			c = c->next;
		}
		cur = cur->next;
		printf("\n");
	}
}

// https://www.geeksforgeeks.org/wildcard-character-matching/
// How to deferienciate escaped widcards??
// Maybe save the first arg string pointer and process from there when we see an
// Unescaped wildcard

int		wildcard(char *arg, char *file)
{
	if (!*arg || !*file)
		return (1);

	if (ft_strlen(arg) > 1 && *arg == '*' && !*file)
		return (0);
	if (*arg == *file)
		return wildcard(arg + 1, file + 1);
	if (*arg == '*')
		return wildcard(arg + 1, file) || wildcard(arg, file + 1);
	return (0);
}

void	read_var(t_cmd *cur, char *var, char **curread, t_env *env)
{
	int		i;
	char	*parse;
	char	*read;

	parse = get_arg(var, env);
	i = 0;
	read = *curread;
	while (parse[i])
	{
		while (parse[i] == ' ')
		{
			end_arg(&read, NULL, cur, NULL);
			i++;
		}
		if (parse[i])
			read = ft_strnewcat(read, parse + i++, 1);
	}
	*curread = read;
}

t_cmd	*parse(char *parse, t_env *env)
{
	int						i;
	char					*read;
	char					*resp;
	t_cmd					*list;
	t_cmd					*cur;
	enum	e_redirect_type	type = R_NONE;
	bool					quote;

	i = 0;
	read = NULL;
	cur = blank_cmd();
	list = cur;
	quote = false;
	while (parse[i])
	{
		while (parse[i] == ' ')
		{
			end_arg(&read, &type, cur, &quote);
			i++;
		}
		if (parse[i] == ';' || parse[i] == '|')
		{
			end_arg(&read, &type, cur, &quote);
			if (cur->av == NULL)
				return error_clean(list, read, parse[i]);
			next_cmd(&cur, parse[i] == '|');
			i++;
			continue;
		}
		if (parse[i] == '<' || parse[i] == '>')
		{
			end_arg(&read, &type, cur, &quote);
			if (type != R_NONE)
				return error_clean(list, read, parse[i]);
			if (ft_starts_with(parse + i, "<<") && ++i)
				type = RR_INPUT;
			else if (ft_starts_with(parse + i, ">>") && ++i)
				type = RR_OUTPUT;
			else if (ft_starts_with(parse + i, "<") && !ft_starts_with(parse + i + 1, ">"))
				type = R_INPUT;
			else if (ft_starts_with(parse + i, ">") && !ft_starts_with(parse + i + 1, "<"))
				type = R_OUTPUT;
			else
				return error_clean(list, read, parse[i]);
			i++;
			continue;
		}
		if (parse[i] == '\\' && parse[i + 1])
			i++;
		else if (parse[i] == '"' || parse[i] == '\'')
		{
			quote |= parse[i] == '"';
			resp = read_marks(parse + i, &i, parse[i], env);
			if (resp == NULL)
				return error_clean(list, read, parse[i]);
			read = ft_strnewcat(read, resp, ft_strlen(resp));
			free(resp);
			continue;
		}
		else if (parse[i] == '$' && type != RR_INPUT)
		{
			int t = 0;
			char *name = extract_var_name(parse + i, &t);
			if (ft_strlen(name) > 0)
			{
				i += t;
				read_var(cur, name, &read, env);
				continue;
			}
			free(name);
		}
		if (parse[i])
			read = ft_strnewcat(read, parse + i++, 1);
	}
	if (!read && type != R_NONE)
		return error_clean(list, read, parse[i]);
	end_arg(&read, &type, cur, &quote);
	return (list);
}
