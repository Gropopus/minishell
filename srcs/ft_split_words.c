/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 10:10:11 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/14 14:37:43 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

void	ft_is_esc(char c, int *is_esc)
{
	if (c == '\\' && *is_esc == 0)
		*is_esc = 1;
	else if (c == '\\' && *is_esc == 1)
		*is_esc = 0;
	else if (c != '\\')
		*is_esc = 0;
}

int		ft_is_sep(char c, char *sep)
{
	int i = 0;
	while (sep[i])
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int		ft_skip_quotes(char *str, char c, int*i)
{
	int j;
	int	is_esc;
	int	is_empty;

	is_empty = 0;
	is_esc = 0;
	j = *i + 1;
	while (str[j])
	{
		ft_is_esc(str[j], &is_esc);
		if (c == str[j] && is_esc == 0)
			break;
		else if (str[j] != c && is_esc == 0)
			is_empty = 1;
		j++;
	}
	*i = j + 1;
	if (is_empty > 0)
		return (1);
	return (0);
}

void	ft_skip_sep(char *str, int *i)
{
	int		j;
	char	c;

	c = str[*i];
	j = *i;
//	if (c == '\'' || c == '\"')
		//skip quotes;
//	else
//	{
		while (str[j] == c)
			j++;
		*i = j;
//	}
}

int		ft_count_words(char *str)
{
	int i;
	int is_esc = 0;
	int word;

	i = 0;
	word = 0;
	while (str[i])
	{
		ft_is_esc(str[i], &is_esc);
		if (ft_is_sep(str[i + 1], " \t'\"") == 1
			&& ft_is_sep(str[i], " \t'\"") == 0 && is_esc == 0)
		{
			if (str[i + 1] == '\'' || str[i + 1] == '\"')
			{
				i++;
				ft_skip_quotes(str, str[i], &i);
				if (ft_is_sep(str[i], " \t") == 1)
				{
					word++;
				}
			}
			else
			{
				word++;
				ft_skip_sep(str, &i);
			}
		}
		i++;
	}
	return (word);
}

int		main(void)
{
	char *line;
	while (1)
	{
		get_next_line(0, &line);
		ft_printf("count %d\n", ft_count_words(line));
		if (ft_strcmp(line, "exit") == 0)
			return (0);
		free(line);
	}
}
