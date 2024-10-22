
#include "minishell.h"

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
		if (strcmp(key, cur->key) == 0)
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

void	ft_print_lst2(t_env *tok)
{
	t_env	*cur;

	cur = tok;
	while (cur->next)
	{
		printf("%s\n", cur->key);
		printf("%s\n", cur->value);
		cur = cur->next;
	}
	printf("%s\n", cur->key);
	printf("%s\n", cur->value);
}

int	main(int ac, char **av, char **env)
{	
	t_data	data;
	char	*s;
	char	*res;
	char	*val;
	int		i;

	(void)ac;
	(void)av;
	s = "Bon$HOME yo$yo";
	i = 4;
	ft_init_data(&data);
	if (!ft_setup_env(&data, env))
		return (0);
	res = ft_get_key(&data, s, i);
	printf("%s\n", res);
	val = ft_get_value(&data, res);
	printf("%s\n", val);
	free(res);
	free(val);
	//ft_print_lst2(data.env);
	ft_clear_env(&data.env);
	free(data.line);
	return (0);
}