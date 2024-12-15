/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:49:11 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 01:26:24 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	export_dup(char *str, t_env **env)
{
	char	*key;
	char	*value;
	int		pos;
	t_env	*cur;

	cur = *env;
	key = ft_cpy_key2(str);
	value = ft_cpy_value2(str, key);
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

int	export(char *str, t_env **env)
{
	char	*key;
	char	*value;
	int		pos;
	t_env	*cur;

	cur = *env;
	key = ft_cpy_key2(str);
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

	if (cmd && !cmd[1])
		return (ft_print_export(data->dup));
	res = 0;
	i = 0;
	while (cmd[++i])
	{
		equal = 0;
		if (!ft_valid_id(cmd[i], &equal))
			res = ft_print_export_error(cmd[i]);
		else if (equal)
		{
			if (!export(cmd[i], &data->env) || !export(cmd[i], &data->dup))
				ft_clear_all(data, "Malloc error\n", 1);
		}
		else if (!equal)
		{
			if (!export_dup(cmd[i], &data->dup))
				ft_clear_all(data, "Malloc error\n", 1);
		}
	}
	return (res);
}
