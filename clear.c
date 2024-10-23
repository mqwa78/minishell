
#include "minishell.h"

void	ft_clear_garbage(t_data *data, int flag)
{	
	if (flag == 0)
		free(data->line);
	ft_clear_tok(&data->tok);
	ft_clear_env(&data->env);
	ft_putstr_fd("Minishell : Malloc error\n", 2);
	exit(1);
}

void	ft_clear_expand(t_data *data, char *key, char *value, int flag)
{	
	free(key);
	free(value);
	if (flag == 0)
		ft_clear_garbage(data, -1);
}

void	ft_clear_env(t_env **lst)
{
	if (!lst || !(*lst))
		return ;
	ft_clear_env(&(*lst)->next);
	free((*lst)->key);
	free((*lst)->value);
	free(*lst);
	*lst = NULL;
}

void	ft_clear_tok(t_tok **lst)
{
	if (!lst || !(*lst))
		return ;
	ft_clear_tok(&(*lst)->next);
	if ((*lst)->token)
		free((*lst)->token);
	free(*lst);
	*lst = NULL;
}