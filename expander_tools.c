
#include "minishell.h"

char	*ft_erase_quotes(char *s, int size)
{
	char	*new;
	int		sq;
	int		dq;
	int		i;

	sq = 0;
	dq = 0;
	new = malloc(sizeof(char) * ft_strlen(s) - size + 1);
	if (!new)
		return (NULL);
	i = -1;
	size = -1;
	while (s[++i])
	{
		if (!sq || !dq)
			ft_quote(s[i], &dq, &sq);
		new[++size] = s[i];
	}
	new[++size] = '\0';
	free(s);
	return (new);
}

int	ft_count_quotes(char *s)
{
	int	sq;
	int	dq;
	int	i;
	int	count;

	sq = 0;
	dq = 0;
	count = 0;
	i = -1;
	if (!s)
		return (count);
	while (s[++i])
	{
		ft_quote(s[i], &dq, &sq);
		if (s[i] == '\"' && dq && !sq)
			count++;
		else if (s[i] == '\'' && sq && !dq)
			count++;
	}
	return (count * 2);
}

char	*ft_free_and_return(char *new, char *old)
{
	free(old);
	return (new);
}

char	*ft_get_key(t_data *data, char *s, int i)
{	
	char	*key;
	int		count;
	int		j;

	count = 0;
	while (s[i + count] && ft_isalnum(s[i + count]))
		count++;
	key = malloc(sizeof(char) * count + 1);
	if (!key)
		ft_clear_garbage(data, -1);
	j = 0;
	while (j < count)
	{
		key[j] = s[i];
		i++;
		j++;
	}
	key[j] = '\0';
	return (key);
}

char	*ft_get_value(t_data *data, char *key)
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
				free(key);
				ft_clear_garbage(data, -1);
			}
			return (value);
		}
		cur = cur->next;
	}
	value = ft_strdup("");
	if (!value)
	{	
		free(key);
		ft_clear_garbage(data, -1);
	}
	return (value);
}
