/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:30:50 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/18 22:09:13 by mqwa             ###   ########.fr       */
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

void	ft_sigint_here(t_data *data)
{
	data->here = 1;
	data->exit = 130;
}

int	ft_norm_here(int fd, t_data *data, int stdin_backup)
{
	close(fd);
	init_signals(data);
	dup2(stdin_backup, STDIN_FILENO);
	close(stdin_backup);
	return (1);
}

void	ft_clear_spe_here(t_data *data, char *str)
{
	if (str)
		free(str);
	ft_clear_tok(&data->tok);
	ft_clear_all(data, "Malloc error\n", 1);
}
