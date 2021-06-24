/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 18:01:15 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 18:35:27 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

char	*ft_strnewcat(char *s, char *o, int len)
{
	int		i;
	int		j;
	char	*n;

	n = malloc(ft_strlen(s) + len + 2);
	if (n == NULL)
		return (NULL);
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

bool	is_alpha_num(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z') || c == '_');
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

int		wildcard(char *arg, char *file)
{
	if (!*arg || !*file)
		return (1);

	if (ft_strlen(arg) > 1 && *arg == '*' && !*file)
		return (0);
	if (*arg == *file)
		return wildcard(arg + 1, file + 1);
	if (*arg == '*')
		return wildcard(arg + 1, file) || wildcard(arg, file + 1);
	return (0);
}
/*
void	printf_cmds(t_cmd *cur)
{
	int		i;
	char	*rt;

	i = 0;
	while (cur)
	{
		printf(" -------- \n");
		printf(" Piped: %s\n", cur->is_piped ? "YES" : "NO");

		i = 0;
		while (cur->av && cur->av[i])
		{
			printf("ARG[%i]: %s\n", i, cur->av[i]);
			i++;
		}
		t_file_list *c = cur->file;
		while (c)
		{
			rt = "Unk";
			if (c->type == R_INPUT)
				rt = "<";
			if (c->type == RR_INPUT)
				rt = "<<";
			if (c->type == R_OUTPUT)
				rt = ">";
			else if (c->type == RR_OUTPUT)
				rt = ">>";
			printf("REDIR(%s): %s Escaped: %s\n", rt, c->path, c->quote ? "true" : "false");
			c = c->next;
		}
		cur = cur->next;
		printf("\n");
	}
}
*/
