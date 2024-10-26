
#include "minishell.h"

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
