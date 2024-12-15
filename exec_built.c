/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:47:24 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 23:55:55 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_built(int *pip, t_cmd *cmd, t_data *data)
{
	close(pip[0]);
	if (cmd->out < 0 && cmd->next)
		cmd->out = pip[1];
	else
		close(pip[1]);
	launch_builtin(data, cmd);
}

int	launch_builtin(t_data *data, t_cmd *cmd)
{
	int	out;

	out = -1;
	if (cmd->out >= 0)
	{
		out = dup(1);
		dup2(cmd->out, 1);
	}
	exec_built(data, cmd, out);
	if (cmd->out >= 0)
	{
		dup2(out, 1);
		close(out);
	}
	if (cmd->out >= 0)
		close(cmd->out);
	return (1);
}

void	exec_built(t_data *data, t_cmd *cmd, int out)
{
	(void)out;
	if (!ft_strncmp("echo", cmd->tab[0], 5))
		data->exit = ft_echo(cmd->tab);
	else if (!ft_strncmp("env", cmd->tab[0], 4))
		data->exit = ft_env(data->env);
	else if (!ft_strncmp("pwd", cmd->tab[0], 4))
		data->exit = ft_pwd();
	else if (!ft_strncmp("unset", cmd->tab[0], 6))
		data->exit = ft_unset(data, cmd->tab);
	else if (!ft_strncmp("cd", cmd->tab[0], 3))
		data->exit = ft_cd(data, cmd->tab);
	else if (!ft_strncmp("export", cmd->tab[0], 7))
		data->exit = ft_export(data, cmd->tab);
	else if (!ft_strncmp("exit", cmd->tab[0], 5))
	{
		if (cmd->out >= 0)
		{
			dup2(out, 1);
			close(out);
		}
		ft_exit(data, cmd->tab);
	}
}

int	is_built(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("env", cmd, 4))
		return (1);
	else if (!strncmp("pwd", cmd, 4) || !ft_strncmp("unset", cmd, 6))
		return (1);
	else if (!strncmp("cd", cmd, 3) || !ft_strncmp("export", cmd, 7))
		return (1);
	else if (!strncmp("exit", cmd, 5))
		return (1);
	return (0);
}
