
#include "minishell.h"

char	*ft_get_value1(t_data *data, char *key)
{
	t_env	*cur;
	char	*value;

	cur = data->env;
	while (cur)
	{
		if (ft_strcmp(key, cur->key) == 0)
		{
			value = ft_strdup(cur->value);
			if (!value)
			{
				ft_clear_garbage(data, -1);
			}
			return (value);
		}
		cur = cur->next;
	}
	value = ft_strdup("");
	if (!value)
	{
		ft_clear_garbage(data, -1);
	}
	return (value);
}

int	ft_create_elem1(t_env **begin, char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = key;
	new->value = value;
	new->next = *begin;
	*begin = new;
	return (1);
}

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
