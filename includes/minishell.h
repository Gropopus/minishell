/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:26:29 by thsembel          #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <curses.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>

# define NC "\033[0m"
# define RED "\033[0;91m"
# define YELLOW "\033[93m"
# define GREEN "\033[0;92m"
# define PURPLE "\033[0;95m"
# define BLUE "\033[0;34m"
# define BOLD "\033[1m"
# define CYAN "\033[38;6;36m"

/**
	TODO:
	Heredoc
	RM with CD

	Pas urgent:
	When starting a shell with no SHLVL in env, it gets set to 1 by default
	_ in env

	Check:
	$? values
*/

enum e_redirect_type
{
	R_NONE,
	R_INPUT,
	R_OUTPUT,
	RR_INPUT,
	RR_OUTPUT
};

typedef struct s_file_list
{
	char					*path;
	enum e_redirect_type	type;
	int						fd;
	int						pipes[2];
	bool					quote;
	struct s_file_list		*next;
}				t_file_list;

typedef struct s_cmd
{
	int						ac;
	char					**av;
	char					*av_cpy;
	char					*path;
	bool					is_piped;
	int						pipe_open;
	int						pipes[2];
	pid_t					pid;
	t_file_list				*file;
	struct s_cmd			*prev;
	struct s_cmd			*next;
}				t_cmd;

typedef struct s_parser
{
	int						i;
	char					*read;
	char					*resp;
	t_cmd					*list;
	t_cmd					*cur;
	enum e_redirect_type	type;
	bool					quote;
}				t_parser;

typedef struct s_env
{
	char					*var;
	char					*value;
	struct s_env			*next;
}				t_env;

int				ft_extensions(char **cmd_av, t_env *env);
int				ft_env_str_len(char *string);
int				ft_exec_echo(t_cmd *cmds, t_env *env);
int				ft_exec_unset(t_cmd *cmds, t_env *env, bool fork);
int				ft_exec_env(t_cmd *cmds, t_env *env);
int				ft_exec_pwd(t_cmd *cmds, t_env *env);
int				ft_exec_cd(t_cmd *cmds, t_env *env, bool fork);
int				ft_exec_export(t_cmd *cmds, t_env *env, bool fork);
int				ft_exec_exit(t_cmd *cmds, t_env *env, bool fork);
int				exec_cmd(t_cmd *cmds, t_env *env, bool builtin);
int				env_manager(char *var, char *value, t_env *env);
int				cmd_manager(t_cmd *cmds, t_env *env);
int				ft_find_exec(t_cmd *cmds, t_env *env);
int				is_in_builtin(char **cmds);
int				ft_fill_cmds(t_cmd *cmds, t_env *env);
unsigned int	ft_error(unsigned int error);
void			ft_syntax_error(char token);
unsigned int	ft_nice_error(unsigned int error, char *msg);
void			ft_free_env(t_env *env);
void			ft_free_cmd(t_cmd *cmds);
void			ft_str_expand_triple(char **src, char *add1, char *add2);
void			ft_list_sort(t_env **begin_list);
void			get_absolute_path(t_cmd *cmds, t_env *env);
char			**ft_env_to_my_env(t_env *env, int size_env, int i);
char			*ft_env_chr(t_env *env, char *var);
char			*ft_dup_to_equal(char *str, char c);
char			*ft_dup_pass_equal(char *str, char c);
t_env			*ft_env_cpy(unsigned int *error, char **envp);
t_cmd			*parse(char *parse, t_env *env);
int				setup_signals(void);
int				disable_signals(int fork);
char			*get_prompt(t_env *env);
char			*last_error(bool set, int err);
void			ft_free_cmd_stuff(t_cmd *cmds);
/*
	Pipes
*/
int				dup_pipes(int *pipe_open, t_cmd *cmd);
int				close_pipes(int pipe_open, t_cmd *cmd);

/*
**			redirections.c
*/
int				ft_redirection(t_cmd *cmd, t_env *env);
void			ft_close_fd(t_cmd *cmd);
/*
**			redirection2.c
**/
void			ft_dup_fd(t_cmd *cmd);

void			rl_replace_line(const char *line, int r);
/*
	Parsing
*/

t_cmd			*blank_cmd(void);
void			ft_free_list(t_file_list **list);
t_cmd			*error_clean(t_cmd *list, char *r, char n);
void			next_cmd(t_cmd **cur, bool piped);
void			add_redirection(t_cmd *cmd, char *arg,
					enum e_redirect_type type, bool *quote);
char			*read_marks(char *parse, int *cur, char mark, t_env *env);
t_cmd			*parse(char *parse, t_env *env);
void			add_arg(t_cmd *cmd, char *arg);
void			end_arg(char **a, enum e_redirect_type *type, t_cmd *cmd,
					bool *quote);
char			*ft_strnewcat(char *s, char *o, int len);
bool			is_alpha_num(char c);
bool			ft_starts_with(char *s, char *sta);
char			*get_var_value(char *name, t_env *env);
char			*extract_var_name(char *parse, int *cur);
void			read_var(t_cmd *cur, char *var, char **curread, t_env *env);
char			*read_marks(char *parse, int *cur, char mark, t_env *env);
char			*fill_vars(char *str, t_env *env, int i, char *read);

#endif
