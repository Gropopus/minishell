/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 14:37:38 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/18 18:22:58 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

int	ft_expand_dollar(t_env *env, char **cmd_av, char **offset)
{
	char	*var;
	char	*ret;
	char	*value;
	size_t	len;

	ret = ft_strndup(*cmd_av, (*offset - *cmd_av));
	len = ft_env_str_len((*offset) + 1);
	var = ft_strndup((*offset) + 1, len);
	if (ret == NULL || var == NULL || len == 0)
	{
		free(ret);
		free(var);
		if (len == 0)
			(*offset)++;
		return (0);
	}
	value = ft_env_chr(env, var);
	free(var);
	ft_str_expand_triple(&ret, value, (*offset) + len + 1);
	if (ret == NULL)
		return (ft_error(-1));
	*offset = ret + (*offset - *cmd_av) + (ft_strlen(value));
	free(*cmd_av);
	*cmd_av = ret;
	return (0);
}

int	ft_expand_home(char **cmd_av, t_env *env)
{
	char	*temp;
	char	*value;
	int		ret;

	ret = 0;
	temp = *cmd_av;
	if ((temp[0] == '~') && ((temp[1] == '\0') || (temp[1] == '/')))
	{
		value = ft_env_chr(env, "HOME");
		if (value != NULL)
		{
			temp = ft_strjoin(value, (temp + 1));
			if (temp == NULL)
				return (ft_error(1));
			free(*cmd_av);
			*cmd_av = temp;
		}
	}
	return (ret);
}

int	ft_expand(char **cmd_av, t_env *env)
{
	int		ret;
	char	*offset;

	ret = 0;
	if ((*cmd_av)[0] == '~' && ((*cmd_av)[1] == '/' || (*cmd_av)[1] == '\0'))
		ret = ft_expand_home(cmd_av, env);
	offset = ft_strchr(*cmd_av, '$');
	while (offset != NULL && offset != &(*cmd_av)[ft_strlen(*cmd_av) - 1])
	{
		ret = ft_expand_dollar(env, cmd_av, &offset);
		if (ret != 0)
			break ;
		offset = ft_strchr(offset, '$');
	}
	return (ret);
}

int	ft_extansions(char **cmd_av, t_env *env)
{
	int		i;
	int		ret;
	int		final_ret;
	char	*var_start;

	i = 0;
	final_ret = 0;
	while (cmd_av && cmd_av[i] != NULL)
	{
		var_start = ft_strchr(cmd_av[i], '$');
		if (var_start != NULL || cmd_av[i][0] == '~')
		{
			ret = ft_expand(&(cmd_av[i]), env);
			if (ret != 0)
				final_ret = ret;
		}
		i++;
	}
	return (final_ret);
}
