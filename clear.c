
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

int	ft_clear_tok(t_tok **lst)
{
	if (!lst || !(*lst))
		return (1);
	ft_clear_tok(&(*lst)->next);
	if ((*lst)->token)
		free((*lst)->token);
	free(*lst);
	*lst = NULL;
	return (1);
}