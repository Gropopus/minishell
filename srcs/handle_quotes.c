/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:04:12 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/14 10:12:18 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

int		ft_is_to_count(char *str, int i, int start)
{
	int count;
	int j;

	j = i - 1;
	count = 0;
//	ft_printf("start %d, j  %d\n", start, j);
	while (j > start)
	{
		if (str[j] == '\\')
			count++;
		j--;
	}
	if (count % 2 == 0)
		return (1);
	else
		return (0);
}

int		ft_is_char_in_str(char *str, char c, int *j)
{
	int i;
	int start;
	int nbr;

	start = *j;
	i = *j + 1;
	nbr = 0;
	while (str[i])
	{
		if (str[i] == c &&  str[i - 1] != '\\')
				break ;
		else if (str[i] == c && str[i - 1] == '\\' && ft_is_to_count(str, i, start) == 1 && i > 0)
			break ;
		else if (str[i] == c && ft_is_to_count(str, i, start) == 0 && i > 0)
			start = i;
		i++;
	}
	*j = i;
	if (str[i] == '\0')
		return (0);
	return (1);
}

int		cmd_line_isvalid(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if ((ft_is_char_in_str(str, '\"', &i)) == 0)
				return (0);
		}
		else if (str[i] == '\'')
		{
			if ((ft_is_char_in_str(str, '\'', &i)) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}

void	copy_quotes_content(char *str, char buff, int *i, int *j)
{
	int quotes;
	int	k = *i;
	int l = k;
	int end;
	quotes = 0;
	while (str[k])
	{
		if (str[k] == '\'' && str[k - 1] != '\\')
			break;
		else if (str[i] == '\'' && str[i - 1] == '\\' && ft_is_to_count(str, k, l);
			break;
		k++;
	}
	while (*i < k)
	{
		if (str[*i] == '\\')
			quotes++;
		buff[*j] = str[*i];
	}

}

int		ft(char *str)
{
	int i = 0;
	int j = 0;
	char buff[500];

	ft_bzero(buff, 500);
	if ((cmd_line_isvalid(str)) == 0)
		return (0);
	else
	{
		while (str[i] && str[i] != '\'' && str[i] != '\"')
		{
			if (str[i] == ' ' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
			{
				i += 2;
				break;
			}
			buff[j] = str[i];
			i++;
			j++;
		}
		//if (str[i] == '\''')

		//else if (str[i] == '\"')
			
		ft_printf("c->%c\n%s", str[i], buff);
	}
	return (0);
}

int		main(void)
{
	char *line;
	while (1)
	{
		get_next_line(0, &line);
		ft(line);
		if (ft_strcmp(line, "exit") == 0)
			return (0);
		free(line);
	}
}
