/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:06:41 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 22:49:06 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

char	*get_var_value(char *name, t_env *env)
{
	char	*path;

	if (name[0] == '?' && !name[1])
		return (last_error(false, 0));
	path = ft_env_chr(env, name);
	if (path == NULL)
		return ("");
	return (path);
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

char *fill_vars(char *str, t_env *env, int i, char *read)
{
	char	*name;
	char	*val;
	int		t;

	while (str[i])
	{
		if (str[i] == '$')
		{
			t = 0;
			name = extract_var_name(str + i, &t);
			if (ft_strlen(name) > 0)
			{
				i += t;
				val = get_var_value(name, env);
				read = ft_strnewcat(read, val, ft_strlen(val));
				free(name);
				continue ;
			}
			free(name);
		}
		read = ft_strnewcat(read, str + i++, 1);
	}
	return (read);
}

void	read_var(t_cmd *cur, char *var, char **curread, t_env *env)
{
	int		i;
	char	*parse;
	char	*read;

	parse = get_var_value(var, env);
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
