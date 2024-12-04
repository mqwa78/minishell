
#include "minishell.h"

int	ft_check_var_key(char *s)
{
	int	i;

	if (!s || !*s)
		return (0);
	i = 0;
	if (s[i] && !ft_isalpha(s[i]) && s[i] != '_')
		return (1);
	while (s[i])
	{
		if (!ft_isalnum(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_print_unset(char *s, int *error)
{
	ft_putstr_fd("Minishell : unset ", 2);
	ft_putchar_fd('`', 2);
	ft_putstr_fd(s, 2);
	ft_putchar_fd('\'', 2);
	ft_putstr_fd(" : not a valid identifier\n", 2);
	*error = 1;
}

int	ft_del_node(t_env **begin, t_env **node, int flag)
{
	t_env	*tmp;

	if (flag == 0)
	{
		tmp = (*begin);
		(*begin) = (*begin)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (0);
	}
	else if (flag == 1)
	{
		tmp = (*node);
		(*begin)->next = (*node)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		return (0);
	}
	return (1);
}

int	ft_unset_var(t_env **env, char *s)
{
	t_env	*cur;
	t_env	*cur_prev;

	if (!(*env))
		return (0);
	cur_prev = (*env);
	if (!cur_prev->next)
	{
		ft_clear_env(&cur_prev);
		return (0);
	}
	if (ft_strcmp(cur_prev->key, s) == 0)
		return (ft_del_node(env, &cur_prev, 0));
	cur = cur_prev->next;
	while (cur)
	{
		if (ft_strcmp(cur->key, s) == 0)
			return (ft_del_node(&cur_prev, &cur, 1));
		cur_prev = cur_prev->next;
		cur = cur->next;
	}
	return (0);
}

int	ft_unset(t_data *data, char **tab)
{	
	int	i;
	int	error;
	int	res;

	res = 0;
	error = 0;
	if (!tab[1])
		return (res);
	i = 1;
	while (tab[i])
	{
		if (ft_check_var_key(tab[i]))
			ft_print_unset(tab[i], &error);
		else
			res = ft_unset_var(&data->env, tab[i]);
		i++;
	}
	if (error)
		res = error;
	return (res);
}
