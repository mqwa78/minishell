
#include "minishell.h"

int	ft_create_elem(t_env **begin, char *key, char *value)
{
	(*begin) = malloc(sizeof(t_env));
	if (!(*begin))
		return (0);
	(*begin)->key = key;
	(*begin)->value = value;
	(*begin)->next = NULL;
	return (1);
}

int	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

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

int	ft_add_env(t_env **begin, char *key, char *value)
{
	t_env	*new;

	if (!ft_create_elem(&new, key, value))
		return (0);
	if (!ft_lstadd_back(begin, new))
		return (0);
	return (1);
}