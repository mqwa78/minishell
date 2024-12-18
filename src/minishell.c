/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:43:08 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/17 21:39:27 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_sig_pid;

void	ft_init_data(t_data *data)
{
	data->env = NULL;
	data->dup = NULL;
	data->tok = NULL;
	data->cmd = NULL;
	data->line = NULL;
	data->pip[0] = -1;
	data->pip[1] = -1;
	data->here = 0;
	data->exit = 0;
	g_sig_pid = 0;
}

int	minishell(char **env)
{
	t_data	data;

	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (1);
	while (1)
	{
		setup_signal_handlers(0);
		data.line = readline("minishell> ");
		if (!data.line)
			ft_clear_all_env(&data, &data.dup);
		if (!ft_parse(&data))
			continue ;
		if (!executer(&data))
			ft_clear_all(&data, "Malloc error\n", 1);
		ft_clear_cmd(&data.cmd);
	}
	rl_clear_history();
	ft_clear_all(&data, NULL, 0);
	return (0);
}
