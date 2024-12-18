/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:48:08 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/18 02:00:04 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_tokens(t_tok *tok)
{
	int		count;
	t_tok	*cur;

	cur = tok;
	count = 0;
	if (!cur || cur->type == PIPE)
		return (count);
	while (cur && cur->type != PIPE)
	{
		if (cur->type > 6)
			count++;
		cur = cur->next;
	}
	return (count);
}

int	ft_fill_tab(t_cmd **elem, t_tok *tok)
{
	int		size;
	int		i;
	char	**tab;
	t_tok	*cur;

	size = ft_count_tokens(tok);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		return (ft_free_elem(elem, NULL, 0, 0));
	cur = tok;
	i = 0;
	while (cur && cur->type != PIPE && i < size)
	{
		if (cur->type > 6)
		{
			tab[i] = ft_strdup(cur->token);
			if (!tab[i])
				return (ft_free_elem(elem, tab, i, 1));
			i++;
		}
		cur = cur->next;
	}
	tab[i] = 0;
	(*elem)->tab = tab;
	return (1);
}

int	ft_fill_cmd(t_data *data, t_cmd **elem, t_tok *tok)
{
	if (!ft_get_files(data, elem, tok))
	{
		(*elem)->skip = 1;
		if ((*elem)->in >= 0)
			close((*elem)->in);
		if ((*elem)->out >= 0)
			close((*elem)->out);
	}
	if (data->here)
		return (1);
	if (!ft_fill_tab(elem, tok))
		return (0);
	if (!ft_strlen((*elem)->tab[0]))
		(*elem)->nocmd = 1;
	return (1);
}

int	ft_create_cmd(t_data *data, t_cmd **cmd, t_tok *tok)
{
	t_cmd	*new;

	if (!ft_new_cmd(&new))
		ft_clear_builder(data, cmd);
	if (!ft_fill_cmd(data, &new, tok))
		ft_clear_builder(data, cmd);
	if (data->here)
	{
		data->here = 0;
		ft_clear_here(data, cmd);
		return (0);
	}
	if (!ft_lstadd_back4(cmd, new))
		return (0);
	return (1);
}

int	cmd_builder(t_data *data)
{
	t_cmd	*cmd;
	t_tok	*cur;

	cmd = NULL;
	cur = data->tok;
	if (!cur)
		return (0);
	if (!ft_create_cmd(data, &cmd, cur))
		return (0);
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (!ft_create_cmd(data, &cmd, cur->next))
				return (0);
		}
		cur = cur->next;
	}
	data->cmd = cmd;
	ft_clear_tok(&data->tok);
	return (1);
}
