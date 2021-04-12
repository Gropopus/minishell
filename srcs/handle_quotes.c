/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:04:12 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/12 16:00:43 by thsembel         ###   ########.fr       */
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
	ft_printf("start %d, j  %d\n", start, j);
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
	char buff[100];

	ft_bzero(buff, 100);
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
/*	int j = 0;
	int k = 0;
	while (str[j] != '\"')
		j++;
	j++;
	while (j < i)
	{
		buff[k] = str[j];
		j++;
		k++;
	}
*/
	ft_printf("%s", buff);
	return (1);
}
void	ft(char *str)
{
	int s_quote;
	int d_quote;

	//d_quote = ft_is_char_in_str(str, '\"');
	//s_quote = ft_is_char_in_str(str, '\'');
	ft_printf("\n->%d\n", cmd_line_isvalid(str));
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
