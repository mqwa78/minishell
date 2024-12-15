/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:49:24 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/13 21:12:11 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	put_and_return(void)
{
	ft_putchar_fd('\n', 1);
	return (0);
}

int	ft_check_n(char *str)
{	
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] && str[i] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_echo(char **arg)
{
	int	i;
	int	n_op;

	if (!arg || !arg[0])
		return (1);
	if (!arg[1])
		return (put_and_return());
	i = 1;
	n_op = 0;
	while (arg[i] && ft_check_n(arg[i]))
	{
		n_op = 1;
		i++;
	}
	while (arg[i])
	{
		ft_putstr_fd(arg[i], 1);
		if (arg[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (n_op)
		return (0);
	ft_putchar_fd('\n', 1);
	return (0);
}
