/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:47:42 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 01:10:53 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_dup_env(t_data *data, t_env *env)
{
	t_env	*list;
	t_env	*cur;
	char	*key;
	char	*value;

	if (!env)
		return ;
	cur = env;
	list = NULL;
	while (cur)
	{
		key = ft_strdup(cur->key);
		value = ft_strdup(cur->value);
		if (!key || !value || !ft_add_env(&list, key, value))
			ft_clear_all_env(data, &list);
		cur = cur->next;
	}
	data->dup = list;
}

char	*ft_cpy_key(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{	
		key = malloc(sizeof(char) * i + 1);
		if (!key)
			return (NULL);
		i = 0;
		while (str[i] && str[i] != '=')
		{
			key[i] = str[i];
			i++;
		}
		key[i] = '\0';
		return (key);
	}
	return (NULL);
}

char	*ft_cpy_value(char *str, char *key)
{
	char	*value;
	int		count;
	int		i;
	int		len;

	if (!key)
		return (NULL);
	len = (int)ft_strlen(key) + 1;
	count = 0;
	while (str[len + count])
		count++;
	value = malloc(sizeof(char) * (count + 1));
	if (!value)
		return (NULL);
	i = 0;
	while (str[len])
		value[i++] = str[len++];
	value[i] = '\0';
	return (value);
}

int	ft_setup_env(t_data *data, char **env)
{	
	t_env	*list;
	int		i;
	char	*key;
	char	*value;

	if (!env || !(*env))
		return (0);
	i = -1;
	list = NULL;
	while (env[++i])
	{
		key = ft_cpy_key(env[i]);
		value = ft_cpy_value(env[i], key);
		if (!key || !value || !ft_add_env(&list, key, value))
		{
			ft_clear_env(&list);
			return (0);
		}
	}
	data->env = list;
	ft_dup_env(data, data->env);
	return (1);
}
