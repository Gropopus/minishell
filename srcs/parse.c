/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:59:40 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/18 11:59:43 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s && *s)
	{
		s++;
		i++;
	}
	return (i);
}

char *ft_strdup(char *s)
{
	char *d;

	d = malloc(ft_strlen(s) + 1);
	if (d == NULL)
		exit(0);
	while (*s)
	{
		*d = *s;
		s++;
		d++;
	}
	*d = 0;
	return (d);
}

enum e_redirect_type
{
	R_NONE,
	R_INPUT,
	R_OUTPUT,
	RR_INPUT,
	RR_OUTPUT
};

typedef struct	s_file_list
{
	char			*path;
	enum e_redirect_type	type;
	int				fd;
	struct s_file_list	*next;
}				t_file_list;

typedef struct s_cmd
{
	char			**argv;
	bool			is_piped;
	int				pipes[2];
	t_file_list		*file;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}					t_cmd;

char *get_arg(char *name)
{
	return "A          B";
}

char *ft_strnewcat(char *s, char *o, int len)
{
	int i;
	int j;
	char *n;

	n = malloc(ft_strlen(s) + len + 2);
	//A proteger (tout free depuis une variable global)
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

bool is_alpha_num(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_');
}

char *extract_var_name(char *parse, int *cur)
{
	char *read;
	int i;

	read = malloc(1);
	//A proteger (tout free depuis une variable global)
	read[0] = 0;
	i = 1;
	if (parse[i] == '?')
	{
		*cur += 2;
		return ft_strnewcat(read, "?", 1);
	}
	while (parse[i])
	{
		if (!is_alpha_num(parse[i]))
		{
			*cur += i;
			return read;
		}
		read = ft_strnewcat(read, parse + i++, 1);
	}
	*cur += i;
	return read;
}



char *read_marks(char *parse, int *cur, char mark)
{
	char *read;
	int i;

	read = malloc(1);
	//A proteger (tout free depuis une variable global)
	read[0] = 0;
	i = 1;
	while (parse[i])
	{
		if (parse[i] == mark)
		{
			*cur += i + 1;
			return read;
		}
		if (mark == '"' && parse[i] == '\\' && (parse[i + 1] == '\\'
			|| parse[i + 1] == mark || parse[i + 1] == '$'))
			i++;
		else if (mark == '"' && parse[i] == '$')
		{
			int t = 0;
			char *name = extract_var_name(parse + i, &t);
			if (ft_strlen(name) > 0)
			{
				i += t;
				char *value = get_arg(name);
				free(name);
				read = ft_strnewcat(read, value, ft_strlen(value));
				continue;
			}
			free(name);
		}
		read = ft_strnewcat(read, parse + i++, 1);
	}
	free(read);
	read = NULL;
	return read;
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


void error_clean(t_cmd *list, char *r)
{
	int i;

	if (r)
		free(r);
	while (list)
	{
		i = 0;
		while (list->argv[i])
			free(list->argv[i++]);
		free(list->argv);
		ft_free_list(&list->file);
		list = list->next;
	}
	printf("Parse error\n");
	exit(0);
}

t_cmd	*blank_cmd()
{
	t_cmd *cmd;

	cmd = malloc(sizeof(t_cmd));
	//A proteger (tout free depuis une variable global)

	cmd->argv = NULL;
	cmd->is_piped = false;
	cmd->file = NULL;
	cmd->prev = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_arg(t_cmd *cmd, char *arg)
{
	int c;
	int i;
	char **vnew;

	c = 0;
	while (cmd->argv && cmd->argv[c])
		c++;
	i = 0;
	vnew = malloc(sizeof(char*) * (c + 2));
	//A proteger (tout free depuis une variable global)
	while (i < c)
	{
		vnew[i] = cmd->argv[i];
		i++;
	}
	vnew[i++] = arg;
	vnew[i] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = vnew;
}

void add_redirection(t_cmd *cmd, char *arg, enum e_redirect_type type)
{
	t_file_list *new;
	t_file_list *c;

	new = malloc(sizeof(t_file_list));
	//A proteger (tout free depuis une variable global)
	new->path = arg;
	new->type = type;
	new->next = NULL;

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

void end_arg(char **a, enum e_redirect_type *type, t_cmd *cmd)
{
	if (*a && **a)
	{
		if (!type || *type == R_NONE)
			add_arg(cmd, *a);
		else
			add_redirection(cmd, *a, *type);
		*a = NULL;
		if (type)
			*type = R_NONE;
	}
}

void next_cmd(t_cmd **cur, bool piped)
{
	(*cur)->next = blank_cmd();
	*cur = (*cur)->next;
	if (piped)
		(*cur)->is_piped = piped;
}

/*
http://www.compciv.org/topics/bash/variables-and-substitution/
Variable names can contain a sequence of alphanumeric characters and underscores. For variables created by you, the user, they should start with either an alphabetical letter or an underscore (i.e. not a number):

*/


void printf_cmds(t_cmd *cur)
{
	int i;

	i = 0;
	while (cur)
	{
		printf(" -------- \n");
		printf(" Piped: %s\n", cur->is_piped ? "YES" : "NO");

		i = 0;
		while (cur->argv[i])
		{
			printf("ARG[%i]: %s\n", i, cur->argv[i]);
			i++;
		}

		t_file_list *c = cur->file;
		while (c)
		{
			char *rt = "Unk";
			if (c->type == R_INPUT)
				rt = "<";
			if (c->type == RR_INPUT)
				rt = "<<";
			if (c->type == R_OUTPUT)
				rt = ">";
			else if (c->type == RR_OUTPUT)
				rt = ">>";
			printf("REDIR(%s): %s\n", rt, c->path);
			c = c->next;
		}
		cur = cur->next;
		printf("\n");
	}
}

void read_var(t_cmd *cur, char *var, char **curread)
{
	int i;
	char *parse;
	char *read;

	parse = get_arg(var);
	i = 0;
	read = *curread;
	while (parse[i])
	{
		while (parse[i] == ' ')
		{
			end_arg(&read, NULL, cur);
			i++;
		}
		if (parse[i])
			read = ft_strnewcat(read, parse + i++, 1);
	}
	*curread = read;
	//end_arg(&read, NULL, cur);
}

int main(int argc, char **argv, char **env)
{

	char *parse = "echo \"test\" < file > file test\"test\" | echo $TEST\"$TEST\"$TEST";
	printf("\n\n%s\n\n", parse);

	int i = 0;

	char *read = NULL;
	char *resp;

	t_cmd *list;
	t_cmd *cur;

	cur = blank_cmd();
	list = cur;

	enum e_redirect_type type = R_NONE;

	while (parse[i])
	{
		while (parse[i] == ' ')
		{
			end_arg(&read, &type, cur);
			i++;
		}
		if (parse[i] == ';' || parse[i] == '|')
		{
			if (cur->argv == NULL)
			{
				error_clean(list, read);
			}
			end_arg(&read, &type, cur);
			next_cmd(&cur, parse[i] == '|');
			i++;
			continue;
		}
		if (parse[i] == '<' || parse[i] == '>')
		{
			end_arg(&read, &type, cur);
			if (type != R_NONE)
			{
				error_clean(list, read);
			}
			if (ft_starts_with(parse + i, "<<") && ++i)
				type = RR_INPUT;
			else if (ft_starts_with(parse + i, ">>") && ++i)
				type = RR_OUTPUT;
			else if (ft_starts_with(parse + i, "<") && !ft_starts_with(parse + i + 1, ">"))
				type = R_INPUT;
			else if (ft_starts_with(parse + i, ">") && !ft_starts_with(parse + i + 1, "<"))
				type = R_OUTPUT;
			else
			{
				error_clean(list, read);
			}
			i++;
			continue;
		}
		if (parse[i] == '\\' && parse[i + 1])
			i++;
		else if (parse[i] == '"' || parse[i] == '\'')
		{
			resp = read_marks(parse + i, &i, parse[i]);
			if (resp == NULL)
			{
				error_clean(list, read);
			}
			read = ft_strnewcat(read, resp, ft_strlen(resp));
			free(resp);

			continue;
		}
		else if (parse[i] == '$')
		{
			int t = 0;
			char *name = extract_var_name(parse + i, &t);
			if (ft_strlen(name) > 0)
			{
				i += t;
				read_var(cur, name, &read);
				continue;
			}
			free(name);
		}

		if (parse[i])
			read = ft_strnewcat(read, parse + i++, 1);
	}
	if (!read && type != R_NONE)
	{
		error_clean(list, read);
	}
	end_arg(&read, &type, cur);
	printf_cmds(list);
}
