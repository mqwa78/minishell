/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:49:18 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/12 22:49:20 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	t_env	*cur;

	cur = env;
	if (!cur)
		return (1);
	while (cur != NULL)
	{
		ft_putstr_fd(cur->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(cur->value, 1);
		ft_putchar_fd('\n', 1);
		cur = cur->next;
	}
	return (0);
}
