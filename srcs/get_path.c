/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 10:50:12 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/07 16:12:11 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/ft_printf.h"

void	exec_cmd(char **cmd)
{
	pid_t	pid;
	int		status;
	
	status = 0;
	pid = fork();
	if (pid == -1)
		ft_printf("fork failed");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		kill(pid, SIGTERM);
	}
	else
	{
		ft_printf("cmd0->%s\n", cmd[0]);
		if (execve(cmd[0], cmd, NULL) == -1)
			ft_printf("shell comand failed");
		exit(EXIT_FAILURE);
	}
}

char		*loop_get_path(char **cmds, char **splited_paths, char *bin)
{
	int		i;

	i = 0;
	while (splited_paths[i])
	{
		if ((bin = (char *)ft_calloc(sizeof(char),
		(ft_strlen(splited_paths[i]) + 1 + ft_strlen(cmds[0]) + 1))) == NULL)
			return (NULL);
		ft_strcpy(bin, splited_paths[i]);
		ft_strcat(bin, "/");
		ft_strcat(bin, cmds[0]);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		bin = NULL;
		i++;
	}
	return (NULL);
}

void		get_absolute_path(char **cmds)
{
	char	*path;
	char	*bin;
	char	**splited_paths;

	bin = NULL;
	path = ft_strdup(getenv("PATH"));
	if (path == NULL)
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/bin:/usr/local/sbin");
	if (cmds[0][0] != '/' && ft_strncmp(cmds[0], "./", 2) != 0)
	{
		splited_paths = ft_split(path, ':');
		free(path);
		bin = loop_get_path(cmds, splited_paths, bin);
		ft_free_tab(splited_paths);
		free(cmds[0]);
		cmds[0] = bin;
	}
	else
		free(path);
	if (cmds[0] == NULL)
		printf("Command not found\n");
	else
		exec_cmd(cmds);
}
