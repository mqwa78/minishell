
#include "minishell.h"

int	ft_new_token(t_tok **begin, char *str, int type)
{
	(*begin) = malloc(sizeof(t_tok));
	if (!(*begin))
		return (0);
	(*begin)->token = str;
	(*begin)->type = type;
	(*begin)->next = NULL;
	(*begin)->prev = NULL;
	return (1);
}

int	ft_lstadd_back2(t_tok **lst, t_tok *new)
{
	t_tok	*tmp;

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
	new->prev = tmp;
	return (1);
}

int	ft_create_spe(t_tok **begin, char *str, int type)
{
	t_tok	*new;
	char	*tmp;

	tmp = ft_strdup(str);
	if (!ft_new_token(&new, tmp, type))
		return (0);
	if (!ft_lstadd_back2(begin, new))
		return (0);
	return (1);
}

int	ft_create_token(t_tok **begin, char *str, int type)
{
	t_tok	*new;

	if (!ft_new_token(&new, str, type))
		return (0);
	if (!ft_lstadd_back2(begin, new))
		return (0);
	return (1);
}
