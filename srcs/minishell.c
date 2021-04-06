/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/06 15:21:43 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include "../includes/minishell.h"
# include <stdio.h>

void	write_prompt(void)
{
	write(1, "\033[0;36m", 8);
	write(1, "MyZsh$", 6);
	write(1, "\033[0m", 5);
}

void		ft_minishell(void)
{
	char **tab;
	char *line;
	int end = 1;

	while (end == 1)
	{
		ft_printf("%s%sMyZsh$%s", BOLD, CYAN, NC);
		get_next_line(0, &line);
		tab = ft_split_str(line, " \t");
		free(line);
		if (ft_strncmp(line, "exit", ft_strlen("exit")) == 0)
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
