/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:08:51 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/07 15:23:32 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

#include "libft.h"
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
# define CYAN "\033[0;36m"

typedef struct		s_info
{
	char	**cmds;
	char	*line;
	
}					t_info;

void		exec_cmd(char **cmd);
void		get_absolute_path(char **cmds);
char		**ft_split_str(char *str, char *charsep);

# endif
