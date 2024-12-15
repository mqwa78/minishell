/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:44:32 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/12 22:44:36 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_garbage_env(t_data *data)
{
	ft_clear_cmd(&data->cmd);
	ft_clear_env(&data->env);
	ft_putstr_fd("Minishell : Malloc error\n", 2);
	exit(1);
}

int	ft_count_env_elem(t_env *env)
{
	int		count;
	t_env	*cur;

	count = 0;
	cur = env;
	if (!cur)
		return (count);
	while (cur)
	{
		count++;
		cur = cur->next;
	}
	return (count);
}

char	*ft_fill_env(t_env *env)
{
	char	*str;
	int		size;
	int		i;
	int		j;

	size = ft_strlen(env->key) + ft_strlen(env->value) + 1;
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (env->key[j])
			str[i++] = env->key[j++];
		str[i++] = '=';
		j = 0;
		while (env->value[j])
			str[i++] = env->value[j++];
	}
	str[i] = 0;
	return (str);
}

char	**ft_lst_to_array(t_data *data)
{
	char	**tab;
	int		size;
	int		i;
	t_env	*cur;

	cur = data->env;
	size = ft_count_env_elem(cur);
	tab = malloc(sizeof(char *) * (size + 1));
	if (!tab)
		ft_clear_builder(data, &data->cmd);
	i = 0;
	while (cur && i < size)
	{
		tab[i] = ft_fill_env(cur);
		if (!tab[i])
		{
			ft_clear_tab2(tab, i);
			ft_clear_garbage_env(data);
		}
		cur = cur->next;
		i++;
	}
	tab[i] = 0;
	return (tab);
}
