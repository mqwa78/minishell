/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:52:47 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/15 02:32:48 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_only_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] && !ft_isdigit(str[i]) && !ft_isoperator(str[i]))
		return (0);
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	ft_check_range(unsigned long long nb, int m, int *err)
{
	if (m == 1 && nb > LONG_MAX)
		*err = 1;
	else if (m == -1 && nb > -(unsigned long)LONG_MIN)
		*err = 1;
	return (*err);
}

long long	ft_atol(char *str, int *err)
{
	unsigned long long	res;
	int					m;

	m = 1;
	res = 0;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			m = -m;
		str++;
	}
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		if (ft_check_range(res, m, err))
			break ;
		str++;
	}
	return (m * res);
}

int	validate_exit_status(char *arg, int *err)
{
	unsigned long long	nb;

	nb = 0;
	if (!arg || !*arg || !ft_only_digits(arg))
	{
		*err = 1;
		return (1);
	}
	nb = ft_atol(arg, err);
	return (nb % 256);
}

void	ft_exit(t_data *data, char **args)
{
	long long	exit_status;
	int			err;

	exit_status = 0;
	err = 0;
	if (args[1])
	{
		exit_status = validate_exit_status(args[1], &err);
		if (err)
			print_exit_error(data, args[1]);
	}
	if (args[1] && args[2])
	{
		print_error("exit\n");
		print_error("minishell: exit: too many arguments\n");
		data->exit = 2;
		return ;
	}
	write(1, "exit\n", 5);
	if (!args[1])
		ft_clear_all(data, NULL, data->exit);
	ft_clear_all(data, NULL, exit_status);
}
