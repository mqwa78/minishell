/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 01:10:03 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/14 01:18:28 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_cpy_key2(char *str)
{
	char	*key;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	key = malloc(sizeof(char) * (i + 1));
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

char	*ft_cpy_value2(char *str, char *key)
{
	char	*value;
	int		count;
	int		i;
	int		len;

	if (!key)
		return (NULL);
	len = (int)ft_strlen(key);
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
