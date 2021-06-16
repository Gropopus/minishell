/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:29:58 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/16 14:15:30 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*loop_get_path(t_cmd *cmds, char **splited_paths, char *bin)
{
	int	i;

	i = 0;
	while (splited_paths[i])
	{
		bin = (char *)ft_calloc(sizeof(char),
				(ft_strlen(splited_paths[i]) + ft_strlen(cmds->av[0]) + 2));
		if (bin == NULL)
			return (NULL);
		ft_strcpy(bin, splited_paths[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmds->av[0]);
		cmds->av_cpy = ft_strdup(cmds->av[0]);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		bin = NULL;
		i++;
	}
	return (NULL);
}

void	get_absolute_path(t_cmd *cmds)
{
	char	*bin;
	char	**splited_paths;

	bin = NULL;
	cmds->path = ft_strdup(getenv("PATH"));
	if (cmds->path == NULL)
		cmds->path
			= ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmds->av[0][0] != '/' && ft_strncmp(cmds->av[0], "./", 2) != 0)
	{
		splited_paths = ft_split(cmds->path, ':');
		bin = loop_get_path(cmds, splited_paths, bin);
		ft_free_tab(splited_paths);
		free(cmds->av[0]);
		cmds->av[0] = bin;
	}
	else
		free(cmds->path);
	if (cmds->av[0] == NULL)
		return ;
}

int	ft_find_exec(t_cmd *cmds, t_env *env)
{
	int		ret;

	(void)env;
	ret = 0;
	if (is_in_builtin(cmds->av) != 0)
		cmds->path = ft_strdup("\0");
	else if (ft_strchr(cmds->av[0], '/') != 0)
		cmds->path = ft_strdup(cmds->av[0]);
	else
		get_absolute_path(cmds);
	return (ret);
}
