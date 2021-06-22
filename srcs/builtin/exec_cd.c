/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/09 13:01:02 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/22 15:14:57 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

void	ft_cd_error(char *path, int error, bool fork)
{
	if (!fork)
		return ;
	if (error == ENOTDIR)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else if (error == ENOENT)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}

char	*ft_env_chr(t_env *env, char *var)
{
	t_env	*actual;

	actual = env;
	while (actual)
	{
		if (ft_strcmp(var, actual->var) == 0)
		{
			return (actual->value);
		}
		actual = actual->next;
	}
	return (NULL);
}

char	*ft_find_path(t_cmd *cmds, t_env *env, bool fork)
{
	int		ret;
	char	*path;

	ret = 0;
	if (cmds->ac < 2)
	{
		path = ft_env_chr(env, "HOME");
		if (path == NULL && fork)
			ft_putstr_fd("cd : HOME not set\n", 2);
	}
	else
	{
		if (cmds->av[1][0] == '-' && cmds->av[1][1] == '\0')
		{
			path = ft_env_chr(env, "OLDPWD");
			if (path == NULL && fork)
				ft_putstr_fd("cd : OLDPWD not set\n", 2);
			else if (fork)
				ft_printf("%s\n", path);
		}
		else
			path = cmds->av[1];
	}
	return (path);
}

int	ft_exec_cd(t_cmd *cmds, t_env *env, bool fork)
{
	int		ret;
	char	*previous_path;
	char	*path;

	path = ft_find_path(cmds, env, fork);
	if (path == NULL)
		return (4);
	previous_path = getcwd(NULL, 0);
	ret = chdir(path);
	if (ret != 0)
		ft_cd_error(path, errno, fork);
	else
	{
		if (previous_path)
			env_manager("OLDPWD", previous_path, env);
		path = getcwd(NULL, 0);
		if (path == NULL)
			return (4);
		env_manager("PWD", path, env);
		free(path);
	}
	free(previous_path);
	return (ret);
}
