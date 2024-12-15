/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:46:08 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/13 20:29:28 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exp_q(t_exp **exp)
{
	int	res;

	if (!exp || !(*exp))
		return (1);
	while ((*exp)->sq == 2)
		(*exp) = (*exp)->next;
	res = (*exp)->sq;
	(*exp) = (*exp)->next;
	return (res);
}

int	ft_lstadd_back3(t_exp **lst, t_exp *new)
{
	t_exp	*tmp;

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
	new->prev = tmp;
	return (1);
}

int	ft_new_exp(t_exp **begin, int sq)
{
	(*begin) = malloc(sizeof(t_exp));
	if (!(*begin))
		return (0);
	(*begin)->sq = sq;
	(*begin)->next = NULL;
	(*begin)->prev = NULL;
	return (1);
}

void	ft_add_elem_exp(t_data *data, t_exp **begin, int sq)
{
	t_exp	*new;

	if (!ft_new_exp(&new, sq))
	{
		ft_clear_exp(begin);
		ft_clear_garbage(data, 1);
	}
	if (!ft_lstadd_back3(begin, new))
	{
		ft_clear_exp(begin);
		ft_clear_garbage(data, 1);
	}
}

void	ft_create_lst_exp(t_data *data, t_exp **exp, char *s)
{
	int	i;
	int	etat;
	int	dq;
	int	sq;

	i = -1;
	dq = 0;
	sq = 0;
	etat = 0;
	while (s[++i])
	{
		ft_quote(s[i], &dq, &sq);
		if (s[i] == '$' && s[i + 1] && ft_isalnum(s[i + 1]))
		{
			ft_add_elem_exp(data, exp, sq);
			etat = 1;
		}
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			ft_add_elem_exp(data, exp, sq);
			etat = 1;
		}
	}
	if (exp && etat)
		ft_add_elem_exp(data, exp, 2);
}
