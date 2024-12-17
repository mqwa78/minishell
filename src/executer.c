/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:46:34 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/17 17:58:24 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redirect(t_cmd *cmd, int *pip)
{
	close(pip[0]);
	if (cmd->in >= 0)
	{
		dup2(cmd->in, STDIN_FILENO);
		close(cmd->in);
	}
	if (cmd->out >= 0)
	{
		dup2(cmd->out, STDOUT_FILENO);
		close(cmd->out);
	}
	else if (cmd->next != NULL)
		dup2(pip[1], STDOUT_FILENO);
	close(pip[1]);
}

void	parent_process(t_cmd *cmd, int *pip)
{
	close(pip[1]);
	if (cmd->in >= 0)
		close(cmd->in);
	if (cmd->in == -2)
		cmd->in = pip[0];
	if (cmd->next != NULL && cmd->next->in == -2)
		cmd->next->in = pip[0];
	else
		close(pip[0]);
}

void	child_process(t_data *data, t_cmd *cmd, int *pip)
{
	char	*path;
	char	**env;

	path = NULL;
	if (is_built(cmd->tab[0]))
		setup_built(pip, cmd, data);
	else if (command_exists(&path, data, cmd->tab[0]))
	{
		ft_redirect(cmd, pip);
		env = ft_lst_to_array(data);
		if (!env)
			ft_clear_all(data, "Malloc error\n", 1);
		rl_clear_history();
		execve(path, cmd->tab, env);
		perror("execve");
		free(env);
	}
	if (path)
		free(path);
	ft_clear_all(data, NULL, data->exit);
}

int	exec_cmd(t_data *data, t_cmd *cmd, int *pip)
{
	setup_signal_handlers(1);
	g_sig_pid = fork();
	if (g_sig_pid < 0)
		ft_clear_all(data, "Fork error\n", 1);
	else if (g_sig_pid == 0)
	{
		if (!cmd->skip && cmd->tab && cmd->tab[0] && !cmd->nocmd)
			child_process(data, cmd, pip);
		else
			ft_clear_all(data, NULL, 0);
	}
	else
		parent_process(cmd, pip);
	return (1);
}

int	executer(t_data *data)
{
	t_cmd	*cur;

	cur = data->cmd;
	if (cur && !cur->skip && !cur->next && cur->tab[0] && is_built(cur->tab[0]))
		return (launch_builtin(data, cur));
	if (pipe(data->pip) == -1)
		ft_clear_all(data, "pipe error\n", 1);
	exec_cmd(data, cur, data->pip);
	cur = cur->next;
	while (cur)
	{
		if (pipe(data->pip) == -1)
			ft_clear_all(data, "pipe error\n", 1);
		exec_cmd(data, cur, data->pip);
		cur = cur->next;
	}
	wait_all(data);
	return (1);
}
