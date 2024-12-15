/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:42:30 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 00:05:05 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_quotes(char *s)
{	
	int	sq;
	int	dq;
	int	i;

	sq = 0;
	dq = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 && !dq && !sq)
			dq = 1;
		else if (s[i] == 39 && !sq && !dq)
			sq = 1;
		else if (s[i] == 34 && dq)
			dq = 0;
		else if (s[i] == 39 && sq)
			sq = 0;
	}
	if (sq || dq)
		return (1);
	return (0);
}

void	ft_quote(char c, int *dq, int *sq)
{
	if (c == 34 && !*dq && !*sq)
		*dq = 1;
	else if (c == 39 && !*sq && !*dq)
		*sq = 1;
	else if (c == 34 && *dq)
		*dq = 0;
	else if (c == 39 && *sq)
		*sq = 0;
}

int	ft_only_spaces(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (1);
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse(t_data *data)
{	
	if (data->line[0] == '\0')
		return (ft_print_parse(data, 0));
	add_history(data->line);
	if (ft_only_spaces(data->line))
		return (ft_print_parse(data, 0));
	if (ft_open_quotes(data->line))
		return (ft_print_parse(data, 1));
	if (tokeniser(data, data->line))
		return (0);
	expander(data);
	if (!cmd_builder(data))
		return (0);
	return (1);
}
