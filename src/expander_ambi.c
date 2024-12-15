/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_ambi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:46:20 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 19:31:13 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_ambiguous(char *str)
{
	ft_putstr_fd("Minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ambiguous redirect\n", 2);
}

int	ft_get_pos2(char *key, t_env *env)
{
	int		pos;
	t_env	*cur;

	pos = 1;
	cur = env;
	if (!cur)
		return (-1);
	while (cur)
	{
		if (!strcmp(key, cur->key))
			return (pos);
		pos++;
		cur = cur->next;
	}
	return (-1);
}

int	ft_check_ambi(t_data *data, char *s, int pos)
{
	char	*key;

	key = ft_get_key(data, s, pos);
	if (!key)
		ft_clear_garbage(data, 1);
	if (ft_get_pos2(key, data->env) == -1)
	{
		free(key);
		return (0);
	}
	free(key);
	return (1);
}

void	ft_expand_ambiguous(t_data *data, char *s, int *ambi)
{
	int	i;
	int	dq;
	int	sq;

	dq = 0;
	sq = 0;
	i = 0;
	while (s[i])
	{
		ft_quote(s[i], &dq, &sq);
		if (s[i] == '$' && s[i + 1] && ft_isalnum(s[i + 1]))
		{
			if (!ft_check_ambi(data, s, i + 1))
			{
				ft_print_ambiguous(s);
				*ambi = 1;
			}
		}
		i++;
	}
}

void	ft_check_ambiguous(t_data *data, t_tok *tok)
{
	t_tok	*cur;
	int		ambi;

	cur = tok;
	ambi = 0;
	while (cur)
	{
		if (cur->type == PIPE)
			ambi = 0;
		if (!ambi && cur->type == FILE && cur->prev->type != HEREDOC)
			ft_expand_ambiguous(data, cur->token, &ambi);
		cur = cur->next;
	}
}
