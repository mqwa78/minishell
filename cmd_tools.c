/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:47:50 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/12 22:47:52 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new_cmd(t_cmd **begin)
{
	(*begin) = malloc(sizeof(t_cmd));
	if (!(*begin))
		return (0);
	(*begin)->in = -2;
	(*begin)->out = -2;
	(*begin)->skip = 0;
	(*begin)->tab = NULL;
	(*begin)->next = NULL;
	return (1);
}

int	ft_lstadd_back4(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return (0);
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
