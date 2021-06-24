/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttranche <ttranche@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 18:47:16 by ttranche          #+#    #+#             */
/*   Updated: 2021/06/24 21:54:03 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft.h"

void	ctrl_c(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 0);
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_slash(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 0);
}

void	ignore(int sig)
{
	(void)sig;
	if (sig == SIGINT)
		write(1, "\n", 1);
}

int	setup_signals(void)
{
	if (signal(SIGQUIT, ctrl_slash) < 0)
		return (0);
	if (signal(SIGINT, ctrl_c) < 0)
		return (0);
	return (1);
}

int	disable_signals(int fork)
{
	if (fork == 0)
	{
		if (signal(SIGQUIT, SIG_DFL) < 0)
			return (0);
		if (signal(SIGINT, SIG_DFL) < 0)
			return (0);
	}else{
		if (signal(SIGQUIT, ignore) < 0)
			return (0);
		if (signal(SIGINT, ignore) < 0)
			return (0);
	}
	return (1);
}
