/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:10:44 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/08 00:33:57 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include "../includes/minishell.h"

/*void		exec_built_in(char **cmds)
{
	if (!ft_strcmp(cmds[0], "pwd"))
		ft_printf("%s\n", get_env_var("PWD="));
	else if (!ft_strcmp(cmds[0], "cd"))
		built_in_cd(cmds[1]);
	else if (!ft_strcmp(cmds[0], "env"))
		built_in_env();
}*/

int			is_in_builtin(char **cmds)
{
	int yes;
	int i;

	yes = 0;
	i = 0;
	while (cmds[i])
	{
		if (ft_strcmp(cmds[i], "cd") == 0 || ft_strcmp(cmds[i], "echo") == 0 ||
			ft_strcmp(cmds[i], "pwd") == 0 || ft_strcmp(cmds[i], "env") == 0 ||
			ft_strcmp(cmds[i], "exit") == 0 ||ft_strcmp(cmds[i], "unset") == 0
			|| ft_strcmp(cmds[i], "export") == 0)
			yes++;
		i++;
	}
	if (yes > 0)
		return (1);
	else
		return (0);
}

int		ft_minishell(void)
{
	char **cmds;
	char *line;
	int i;

	i = 0;
	while (1)
	{
		ft_printf("%s%sMyZsh$>%s", BOLD, CYAN, NC);
		get_next_line(0, &line);
		cmds = ft_split_str(line, " \t");
		if (is_in_builtin(cmds))
			ft_printf("is in !\n");
		else
			get_absolute_path(cmds);
		ft_free_tab(cmds);
		free(line);
	}
	return (0);
}

int		main(int ac, char **av, char **envp)
{
	unsigned int	error;
	t_env			*env;
	(void)ac;
	(void)av;
	if ((env = ft_env_cpy(&error, envp)) == NULL) //envp -> NULL
		return (ft_error(error));
}

