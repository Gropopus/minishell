/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 17:29:58 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/25 01:28:50 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

char	*loop_get_path(t_cmd *cmds, char **splited_paths, char *bin, int i)
{
	int			fd;
	struct stat	s;

	while (splited_paths[i])
	{
		bin = (char *)ft_calloc(sizeof(char),
				(ft_strlen(splited_paths[i]) + ft_strlen(cmds->av[0]) + 2));
		if (bin == NULL)
			return (NULL);
		ft_strcpy(bin, splited_paths[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmds->av[0]);
		if (!cmds->av_cpy)
			cmds->av_cpy = ft_strdup(cmds->av[0]);
		fd = open(bin, O_RDONLY);
		if (fstat(fd, &s) != -1)
		{
			close(fd);
			return (bin);
		}
		free(bin);
		bin = NULL;
		i++;
	}
	return (NULL);
}

void	get_absolute_path(t_cmd *cmds, t_env *env)
{
	char	*bin;
	char	**splited_paths;

	bin = NULL;
	cmds->path = ft_strdup(ft_env_chr(env, "PATH"));
	if (cmds->path == NULL)
		return ;
	if (cmds->av[0][0] != '/' && ft_strncmp(cmds->av[0], "./", 2) != 0)
	{
		splited_paths = ft_split(cmds->path, ':');
		bin = loop_get_path(cmds, splited_paths, bin, 0);
		ft_free_tab(splited_paths);
		free(cmds->av[0]);
		cmds->av[0] = bin;
	}
	else
	{
		free(cmds->path);
		cmds->path = NULL;
	}
	if (cmds->av[0] == NULL)
		return ;
}

int	ft_find_exec(t_cmd *cmds, t_env *env)
{
	int		ret;

	(void)env;
	ret = 0;
	cmds->av_cpy = NULL;
	if (cmds->av == NULL)
		return (0);
	if (is_in_builtin(cmds->av) != 0)
		cmds->path = ft_strdup("\0");
	else if (ft_strchr(cmds->av[0], '/') != 0)
		cmds->path = ft_strdup(cmds->av[0]);
	else
		get_absolute_path(cmds, env);
	return (ret);
}
