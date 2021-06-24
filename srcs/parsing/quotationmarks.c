/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotationmarks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 19:07:14 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 19:14:40 by ttranche         ###   ########.fr       */
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
	int		i;

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
			continue ;
		read = ft_strnewcat(read, parse + i++, 1);
	}
	free(read);
	read = NULL;
	return (read);
}
