/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:58:51 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 18:31:54 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

char		*ft_cpy_var(t_env *env)
{
	char	*str;
	int		i;

	if ((str = malloc(sizeof(char) * (ft_strlen(env->var) +
		ft_strlen(env->value) + 1))) == NULL)
		return (NULL);
	i = ft_strlen(env->var);
	str[i] = '=';
	i++;
	ft_memcpy(str, env->var, ft_strlen(env->var));
	ft_memcpy(&(str[i]), env->value, ft_strlen(env->value));
	return (str);
}

char		**ft_env_to_my_env(t_env *env, int size_env, int i)
{
	t_env	*tmp;
	char	**my_env;

	tmp = env;
	while (tmp)
	{
		size_env++;
		tmp = tmp->next;
	}
	if ((my_env = malloc(sizeof(char *) * (size_env + 1))) == NULL)
		return (NULL);
	my_env[size_env] = 0;
	tmp = env;
	while (i < size_env && tmp)
	{
		my_env[i] = ft_cpy_var(tmp);
		if (!my_env[i])
			return (NULL);
		i++;
		tmp = tmp->next;
	}
	return (my_env);
}

int			ft_fill_cmds(t_cmd *cmds, t_env *env)
{
	int ret;

	ret = 0;
	if (cmds->line)
	{
		cmds->av = ft_split_str(cmds->line, " \t\n");
		if (cmds->av)
		{
			if ((cmds->my_env = ft_env_to_my_env(env, 0, 0)) == NULL)
			{
				ft_error(1);
				return (1);
			}
			else
			cmds->ac = ft_tab_len(cmds->av);
		}
	}
	else
	{
		ft_free_cmd(cmds);
		return (ret);
	}
	return (0);
}
