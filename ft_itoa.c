/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:44:43 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/12 22:44:46 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_digits(int n)
{
	size_t	count;
	long	nb;

	count = 1;
	nb = n;
	if (nb < 0)
	{
		count++;
		nb = -nb;
	}
	while (nb >= 10)
	{
		count++;
		nb /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		i;

	nb = n;
	i = ft_count_digits(n);
	str = malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		*str = '-';
		nb = -nb;
	}
	str[i] = 0;
	while (nb >= 10)
	{
		str[--i] = nb % 10 + '0';
		nb /= 10;
	}
	str[--i] = nb % 10 + '0';
	return (str);
}
