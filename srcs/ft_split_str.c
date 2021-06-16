/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:03:03 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/16 14:45:10 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/minishell.h"
#include "../includes/libft.h"

int	ft_find_charsep(char c, char *charsep)
{
	int	i;

	i = 0;
	while (charsep[i] != '\0')
	{
		if (c == charsep[i])
			return (1);
		i++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	ft_count_words(char *str, char *charsep)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		if ((ft_find_charsep(str[i + 1], charsep) == 1
				&& ft_find_charsep(str[i], charsep) == 0))
			word++;
		i++;
	}
	return (word);
}

void	ft_copy_word(char *dest, char *from, char *charsep)
{
	int	i;

	i = 0;
	while (ft_find_charsep(from[i], charsep) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void	ft_transfert(char **strs, char *str, char *charsep)
{
	int	i;
	int	word;
	int	j;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (ft_find_charsep(str[i], charsep) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_find_charsep(str[i + j], charsep) == 0)
				j++;
			strs[word] = malloc(sizeof(char) * (j + 1));
			ft_copy_word(strs[word], str + i, charsep);
			i = i + j;
			word++;
		}
	}
}

char	**ft_split_str(char *str, char *charset)
{
	char	**strs;
	int		word;

	word = ft_count_words(str, charset);
	strs = (char **)malloc(sizeof(char *) * (word + 1));
	if (strs == NULL)
		return (NULL);
	strs[word] = NULL;
	ft_transfert(strs, str, charset);
	return (strs);
}
