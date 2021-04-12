/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 19:30:46 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/12 21:30:47 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

int		is_slashed(char *str, int start, int end)
{
	int i;
	int slash = 0;

	i = end;
	//ft_printf("%c\n", str[i]);
	while (i >= start)
	{
		if (str[i] == '\\')
			slash++;
		i--;
	}
	ft_printf("nb slash->%d\n", slash);
	if (slash % 2 == 0)
		return (1);
	return (0);
}

int		ft_is_quote(char *str, char c, int *i)
{
	int j;
	int k;

	j = *i;
	k = *i;
	while (str[j])
	{
		//if (str[j] == c && is_slashed(str, k, j) == 0)
		//	k = *i;
		if (str[j] == c && is_slashed(str, k, j) == 1)
			return (1);
		j++;
	}
	return (0);
}

int		is_valid(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i - 1] == '\"' && ft_is_quote(str, '\"', &i) == 1)
			return (1);
	//	else if (str[i - 1] == '\'' && ft_is_quote(str, '\'', &i) == 1)
	//		return (1);
		i++;
	}
	return (0);
}

int		main(void)
{
	char *line;

	while ((get_next_line(0, &line)) != 0)
	{
		ft_printf("%d\n", is_valid(line));
		free(line);
	}
	return (0);
}
