/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thsembel <thsembel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 20:35:58 by thsembel          #+#    #+#             */
/*   Updated: 2021/04/07 20:50:34 by thsembel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/ft_printf.h"
# include "../includes/libft.h"
# include "../includes/minishell.h"

unsigned int	ft_error(unsigned int error)
{
	if (error == 0)
		ft_putstr_fd("Unknown error", 2);
	else if (error == 1)
		ft_putstr_fd("Failure to allocate memory", 2);
	else if (error == 2)
		ft_putstr_fd("Permission denied", 2);
	else if (error == 3)
		ft_putstr_fd("Environment var exits and overwrite is off", 2);
	else if (error == 4)
		ft_putstr_fd("Environment var not found", 2);
	else if (error == 5)
		ft_putstr_fd("Environment is empty", 2);
	else if (error == 6)
		ft_putstr_fd("Invalid expansion", 2);
	else if (error == 7)
		ft_putstr_fd("Unable to execute", 2);
	else if (error == 8)
		ft_putstr_fd("Failure in fork process", 2);
	else if (error == 9)
		ft_putstr_fd("Command not found", 2);
	return (error);
}
