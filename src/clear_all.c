/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:48:39 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/15 18:09:51 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_herited_fd(void)
{
	close(1);
	close(2);
	close(0);
}

void	ft_clear_all_env(t_data *data, t_env **list)
{
	ft_clear_env(&data->env);
	ft_clear_env(list);
	exit(1);
}

void	ft_clear_all(t_data *data, char *str, int err)
{
	if (data->cmd)
		ft_clear_cmd(&data->cmd);
	if (data->env)
		ft_clear_env(&data->env);
	if (data->dup)
		ft_clear_env(&data->dup);
	if (data->pip[0] && data->pip[0] != -1)
		close(data->pip[0]);
	if (data->pip[1] && data->pip[1] != -1)
		close(data->pip[1]);
	if (str)
		ft_putstr_fd(str, 2);
	if (!access(HERENAME, F_OK))
		unlink(HERENAME);
	rl_clear_history();
	ft_close_herited_fd();
	exit(err);
}
