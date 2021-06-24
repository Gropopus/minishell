/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 11:59:40 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 19:14:06 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

int	handle_quote_vars(t_parser *p, char *parse, t_env *env, int t)
{
	char	*name;

	if (parse[p->i] == '"' || parse[p->i] == '\'')
	{
		p->quote |= parse[p->i] == '"';
		p->resp = read_marks(parse + p->i, &p->i, parse[p->i], env);
		if (p->resp == NULL)
			return (2);
		p->read = ft_strnewcat(p->read, p->resp, ft_strlen(p->resp));
		free(p->resp);
		return (1);
	}
	else if (parse[p->i] == '$' && p->type != RR_INPUT)
	{
		name = extract_var_name(parse + p->i, &t);
		if (ft_strlen(name) > 0)
		{
			p->i += t;
			read_var(p->cur, name, &p->read, env);
			return (1);
		}
		free(name);
	}
	return (0);
}

int	handle_redirection(t_parser *p, char *parse)
{
	if (parse[p->i] == '<' || parse[p->i] == '>')
	{
		end_arg(&p->read, &p->type, p->cur, &p->quote);
		if (p->type != R_NONE)
			return (2);
		if (ft_starts_with(parse + p->i, "<<") && ++p->i)
			p->type = RR_INPUT;
		else if (ft_starts_with(parse + p->i, ">>") && ++p->i)
			p->type = RR_OUTPUT;
		else if (ft_starts_with(parse + p->i, "<")
			&& !ft_starts_with(parse + p->i + 1, ">"))
			p->type = R_INPUT;
		else if (ft_starts_with(parse + p->i, ">")
			&& !ft_starts_with(parse + p->i + 1, "<"))
			p->type = R_OUTPUT;
		else
			return (2);
		p->i++;
		return (1);
	}
	return (0);
}

int	handle_parse(t_parser *p, char *parse, t_env *env)
{
	int	ret;

	while (parse[p->i] == ' ')
	{
		end_arg(&p->read, &p->type, p->cur, &p->quote);
		p->i++;
	}
	if (parse[p->i] == ';' || parse[p->i] == '\\')
		return (2);
	if (parse[p->i] == '|')
	{
		end_arg(&p->read, &p->type, p->cur, &p->quote);
		if (p->cur->av == NULL && p->cur->file == NULL)
			return (2);
		next_cmd(&p->cur, parse[p->i++] == '|');
		return (1);
	}
	ret = handle_redirection(p, parse);
	if (ret != 0)
		return (ret);
	ret = handle_quote_vars(p, parse, env, 0);
	if (ret != 0)
		return (ret);
	return (0);
}

t_cmd	*parse(char *parse, t_env *env)
{
	t_parser	p;
	int			ret;

	p.i = 0;
	p.read = NULL;
	p.cur = blank_cmd();
	p.list = p.cur;
	p.quote = false;
	p.type = R_NONE;
	if (!parse || !*parse)
		return (NULL);
	while (parse[p.i])
	{
		ret = handle_parse(&p, parse, env);
		if (ret == 1)
			continue ;
		else if (ret == 2)
			return (error_clean(p.list, p.read, parse[p.i]));
		if (parse[p.i])
			p.read = ft_strnewcat(p.read, parse + p.i++, 1);
	}
	end_arg(&p.read, &p.type, p.cur, &p.quote);
	if (p.cur->av == NULL && p.cur->file == NULL)
		return (error_clean(p.list, p.read, parse[p.i]));
	return (p.list);
}
