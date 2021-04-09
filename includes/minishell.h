/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:08:51 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/09 18:22:59 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
#include <errno.h>
#include <curses.h>
#include <term.h>
#include <signal.h>

# define NC "\033[0m"
# define RED "\033[0;91m"
# define YELLOW "\033[93m"
# define GREEN "\033[0;92m"
# define PURPLE "\033[0;95m"
# define BLUE "\033[0;34m"
# define BOLD "\033[1m"
# define CYAN "\033[38;6;36m"

extern char **envp;

typedef struct		s_cmd
{
	int				ac;
	char			**av;
	char			*av_cpy;
	char			*path;
	char			**my_env;
	char			*line;
}				t_cmd;

typedef struct	s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}				t_env;

int				ft_exec_env(t_cmd *cmds, t_env *env);
int				ft_exec_pwd(t_cmd *cmds, t_env *env);
int				ft_exec_cd(t_cmd *cmds, t_env *env);
int				exec_cmd(t_cmd *cmds);
int				env_manager(char *var, char *value, t_env *env);
int				cmd_manager(t_cmd cmds, t_env *env);
int				ft_find_exec(t_cmd *cmds, t_env *env);
int				is_in_builtin(char **cmds);
int				ft_fill_cmds(t_cmd *cmds, t_env *env);
unsigned int	ft_error(unsigned int error);
void			ft_free_env(t_env *env);
void			ft_free_cmd(t_cmd *cmds);
void			ft_exec_exit(t_cmd *cmds, t_env *env);
//void			exec_cmd(char **cmd);
void			get_absolute_path(t_cmd *cmds);
char			*ft_env_chr(t_env *env, char *var);
char			**ft_split_str(char *str, char *charsep);
char			*ft_dup_to_equal(char *str, char c);
char			*ft_dup_pass_equal(char *str, char c);
t_env			*ft_env_cpy(unsigned int *error, char **envp);
# endif
