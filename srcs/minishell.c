/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/06 22:56:56 by thsembel         ###   ########.fr       */
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
	t_list *caps;

	if (!(caps = (t_list *)malloc(sizeof(t_list))))
		return ;
	while (1)
	{
		ft_printf("\n%s%sMyZsh$>%s", BOLD, CYAN, NC);
		get_next_line(0, &line);
		if (ft_strcmp(line, "up") == 0)
		{
			if (caps->next)
				caps = caps->next;
		}
		else
		{
			caps->content = ft_strdup(line);
		}
		ft_printf("acutel:	%s", caps->content);
		tab = ft_split_str(caps->content, " \t");
		ft_lstadd_front(&caps, ft_lstnew(caps->content));
		free(line);
		//	ft_test_env(tab);
		if (ft_strcmp(caps->content, "exit") == 0)
			break ;;
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
