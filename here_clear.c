/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:30:50 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 21:31:13 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_expand_here(t_data *data, char *key, char *value, int flag)
{
	free(key);
	free(value);
	if (flag == 0)
	{
		ft_clear_tok(&data->tok);
		ft_clear_all(data, "Malloc error\n", 1);
	}
}

void	ft_clear_spe_here(t_data *data, char *str)
{
	if (str)
		free(str);
	ft_clear_tok(&data->tok);
	ft_clear_all(data, "Malloc error\n", 1);
}
