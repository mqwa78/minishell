/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:43:27 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/12 22:43:29 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, int n)
{
	while (*s1 && *s1 == *s2 && n)
	{
		s1++;
		s2++;
		n--;
	}
	if (n)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
