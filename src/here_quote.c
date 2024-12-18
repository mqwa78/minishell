/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 21:21:56 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/18 21:54:39 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_here_quote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	ft_clear_quote_here(t_data *data, t_tok **tok)
{
	char	*s;
	int		count;

	s = (*tok)->token;
	count = ft_count_quotes(s);
	if (count == 0)
		return ;
	(*tok)->token = ft_erase_quotes((*tok)->token, count);
	if (!(*tok)->token)
		ft_clear_spe_here(data, NULL);
}
