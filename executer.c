
#include "minishell.h"

int	lunch_built(t_data *data, t_cmd *cmd)
{
	if (!ft_strncmp("echo", cmd->tab[0], 5))
		data->exit = ft_echo(cmd->tab);
	else if (!ft_strncmp("env", cmd->tab[0], 4))
		data->exit = ft_env(data->env);
	else if (!ft_strncmp("pwd", cmd->tab[0], 4))
		data->exit = ft_pwd();
	else if (!ft_strncmp("unset", cmd->tab[0], 6))
		data->exit = ft_unset(data, cmd->tab);
	//else if (!ft_strncmp("export", cmd->tab[0], 7))
	//	data->exit = ft_export(data, cmd->tab);
	return (1);
}

int	is_built(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp("echo", cmd, 5) || !ft_strncmp("env", cmd, 4))
		return (1);
	else if (!strncmp("pwd", cmd, 4) || !ft_strncmp("unset", cmd, 6))
		return (1);
	//else if (!strncmp("export", cmd, 7))
	//	return (1);
	return (0);
}

// add un chek skip_cmd dans premier if

int	executer(t_data *data)
{
	t_cmd	*cur;

	cur = data->cmd;
	if (cur && !cur->next && cur->tab[0] && is_built(cur->tab[0]))
		return (lunch_built(data, cur));
	return (1);
}