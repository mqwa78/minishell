
#include "minishell.h"

int	ft_valid_id(char *str, int *equal)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i++] == '=')
			*equal = 1;
	}
	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_get_pos(char *key, t_env *env)
{
	int		pos;
	t_env	*cur;

	pos = 1;
	cur = env;
	if (!cur)
		return (-1);
	while (cur)
	{
		if (!strcmp(key, cur->key))
			return (pos);
		pos++;
		cur = cur->next;
	}
	return (-1);
}

int	ft_new_value(t_env **env, char *value, int pos)
{
	t_env	*cur;
	int		i;

	cur = *env;
	i = 0;
	while (i++ < pos - 1)
		cur = cur->next;
	free(cur->value);
	cur->value = ft_strdup(value);
	free(value);
	if (!cur->value)
		return (0);
	return (1);
}	

int	export(char *str, t_env **env)
{
	char	*key;
	char	*value;
	int		pos;
	t_env	*cur;

	cur = *env;
	key = ft_cpy_key(str);
	value = ft_cpy_value(str, key);
	if (!key || !value)
		return (0);
	pos = ft_get_pos(key, cur);
	if (pos >= 0)
	{
		free(key);
		if (!ft_new_value(&cur, value, pos))
			return (0);
	}
	else if (pos == -1)
	{
		if (!ft_add_env(env, key, value))
			return (0);
	}
	return (1);
}

int	ft_export(t_data *data, char **cmd)
{
	int	i;
	int	res;
	int	equal;

	if (!cmd)
		return (1);
	if (cmd && !cmd[1])
		return (ft_print_export(data->env));
	res = 0;
	i = 0;
	while (cmd[++i])
	{
		equal = 0;
		if (!ft_valid_id(cmd[i], &equal))
			res = ft_print_export_error(cmd[i]);
		else if (equal)
		{
			if (!export(cmd[i], &data->env))
			{
				ft_putstr_fd("Malloc error\n", 2);
				return (1);
			}
		}
	}
	return (res);
}