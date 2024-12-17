/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:30:50 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/17 19:15:30 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_here(char *str, int fd, int flag)
{
	if (flag == 0)
	{
		ft_putstr_fd("warning: here-document delimited by end-of-file ", 2);
		ft_putstr_fd("(wanted '", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("')\n", 2);
	}
	if (flag == 1)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
	}
}

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
