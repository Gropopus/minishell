/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:59:40 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 18:34:51 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int	read_marks_2(t_env *env, char **read, int *i, char *parse)
{
	char	*name;
	char	*value;
	int		t;

	if (parse[*i] == '$')
	{
		t = 0;
		name = extract_var_name(parse + (*i), &t);
		if (ft_strlen(name) > 0)
		{
			*i += t;
			value = get_var_value(name, env);
			free(name);
			*read = ft_strnewcat(*read, value, ft_strlen(value));
			return (1);
		}
		free(name);
	}
	return (0);
}

char	*read_marks(char *parse, int *cur, char mark, t_env *env)
{
	char	*read;
	int i;

	i = 1;
	read = malloc(1);
	if (read == NULL)
		return (NULL);
	read[0] = 0;
	while (parse[i])
	{
		if (parse[i] == mark)
		{
			*cur += i + 1;
				return (read);
		}
		else if (mark == '"' && read_marks_2(env, &read, &i, parse))
			continue;
		read = ft_strnewcat(read, parse + i++, 1);
	}
	free(read);
	read = NULL;
	return (read);
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
	if (!parse || !*parse)
		return (NULL);
	while (parse[i])
	{
		while (parse[i] == ' ')
		{
			end_arg(&read, &type, cur, &quote);
			i++;
		}
		if (parse[i] == ';' || parse[i] == '\\')
			return error_clean(list, read, parse[i]);
		if (parse[i] == '|')
		{
			end_arg(&read, &type, cur, &quote);
			if (cur->av == NULL && cur->file == NULL)
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
		if (parse[i] == '"' || parse[i] == '\'')
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
	end_arg(&read, &type, cur, &quote);
	if (cur->av == NULL && cur->file == NULL)
		return error_clean(list, read, parse[i]);
	return (list);
}
