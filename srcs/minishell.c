/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/06 17:39:02 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include "../includes/minishell.h"

void		ft_test_env(char **str)
{
	int i;
	char *path;
	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "") == 0)
		{
			path = ft_strdup(getenv("PATH"));
			ft_printf("%s", path);
		}
		i++;
	}
}

void		ft_minishell(void)
{
	char **tab;
	char *line;
	int end = 1;

	while (end == 1)
	{
		ft_printf("%s%sMyZsh$>%s", BOLD, CYAN, NC);
		get_next_line(0, &line);
		tab = ft_split_str(line, " \t");
		free(line);
		ft_test_env(tab);
		if (ft_strcmp(line, "exit") == 0)
			end = 0;
	}
}

int		main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	ft_minishell();
	return (0);
}
