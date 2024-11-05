
#include "minishell.h"

int	ft_new_cmd(t_cmd **begin)
{
	(*begin) = malloc(sizeof(t_cmd));
	if (!(*begin))
		return (0);
	(*begin)->in = 0;
	(*begin)->out = 0;
	(*begin)->cmd = NULL;
	(*begin)->next = NULL;
	return (1);
}

int	ft_lstadd_back4(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return (0);
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
