/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:35:58 by thsembel          #+#    #+#             */
/*   Updated: 2021/06/24 19:46:40 by ttranche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include "../includes/libft.h"
#include "../includes/minishell.h"

char	*last_error(bool set, int err)
{
	static char	*value;

	if (set)
	{
		if (value)
			free(value);
		value = ft_itoa(err);
	}
	else if (!value)
		value = ft_strdup("0");
	return (value);
}

unsigned int	ft_nice_error(unsigned int error, char *msg)
{
	ft_printf("%s%sMinishell:%s", BOLD, CYAN, NC);
	ft_putchar_fd(' ', 2);
	if (msg)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(": ", 2);
	}
	last_error(true, 127);
	return (ft_error(error));
}

void	ft_syntax_error(char token)
{
	ft_printf("%s%sMinishell:%s", BOLD, CYAN, NC);
	ft_putchar_fd(' ', 2);
	ft_putstr_fd("Syntax error near unexpected token '", 2);
	write(2, &token, 1);
	ft_putstr_fd("'\n", 2);
	last_error(true, 1);
}

void	ft_error2(unsigned int error)
{
	if (error == 7)
		ft_putstr_fd("Unable to execute\n", 2);
	else if (error == 8)
		ft_putstr_fd("Failure in fork process\n", 2);
	else if (error == 9)
		ft_putstr_fd("Command not found\n", 2);
	else if (error == 10)
		ft_putstr_fd("Is a directory\n", 2);
	else if (error == 11)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (error == 12)
		ft_putstr_fd("Syntax error\n", 2);
}

unsigned int	ft_error(unsigned int error)
{
	if (error == 0)
		ft_putstr_fd("Unknown error\n", 2);
	else if (error == 1)
		ft_putstr_fd("Failure to allocate memory\n", 2);
	else if (error == 2)
		ft_putstr_fd("Permission denied\n", 2);
	else if (error == 3)
		ft_putstr_fd("Environment var exits and overwrite is off\n", 2);
	else if (error == 4)
		ft_putstr_fd("Environment var not found\n", 2);
	else if (error == 5)
		ft_putstr_fd("Environment is empty\n", 2);
	else if (error == 6)
		ft_putstr_fd("Invalid expansion\n", 2);
	else
		ft_error2(error);
	return (1);
}
