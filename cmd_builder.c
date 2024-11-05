
#include "minishell.h"

// envoyer cur->next qd type == PIPE ?
// on return 0 si un fichier pose probleme quand on l'open

int	ft_create_cmd(t_data *data, t_cmd **cmd, t_tok *tok)
{
	t_cmd	*new;

	if (!ft_new_cmd(&new))
	//	error malloc free cmd et clear garbage;
	//if (!ft_fill_cmd(data, &new))
	//	return (0);
	if (!ft_lstadd_back4(cmd, new))
		return (0);
	return (1);
}

int	cmd_builder(t_data *data)
{
	t_cmd	*cmd;
	t_tok	*cur;

	cur = data->tok;
	if (!cur)
		return (0);
	if (!ft_create_cmd(data, &cmd, cur))
		return (0);
	while (cur)
	{
		if (cur->type == PIPE)
		{
			if (!ft_create_cmd(data, &cmd, cur->next))
				return (0);
		}
		cur = cur->next;
	}
	data->cmd = cmd;
	ft_clear_tok(&data->tok);
	return (1);
}
