/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:46:50 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/12 22:46:55 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*display_cmd_not_found(const char *cmd)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, " : command not found\n", 21);
	return (NULL);
}

char	*extract_paths(t_env *env_list, int len)
{
	t_env	*cur;

	cur = env_list;
	while (len--)
	{
		if (ft_strncmp(cur->key, "PATH", 4) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

int	len_env_list(t_env *lst)
{
	t_env	*cur;
	int		count;

	count = 0;
	cur = lst;
	if (!cur)
		return (count);
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

int	ft_len_cmd(t_cmd *lst)
{
	t_cmd	*cur;
	int		count;

	count = 0;
	cur = lst;
	if (!cur)
		return (count);
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

void	wait_all(t_data *data)
{
	int		status;
	int		pid;
	int		len;
	t_cmd	*tmp;

	tmp = data->cmd;
	len = ft_len_cmd(tmp);
	while (len--)
	{
		pid = waitpid(0, &status, 0);
		if (pid == g_sig_pid)
		{
			if (WIFEXITED(status))
				data->exit = WEXITSTATUS(status);
		}
		if (tmp->out >= 0)
			close(tmp->out);
		if (tmp->in >= 0)
			close(tmp->in);
		tmp = tmp->next;
	}
}
