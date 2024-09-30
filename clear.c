
#include "minishell.h"

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
	free((*lst)->token);
	free(*lst);
	*lst = NULL;
}