
#include "minishell.h"

void	ft_cpy_simple(char *s, char **new, int *i, int *j)
{
	*i += 1;
	while (s[*i] && s[*i] != '\'')
	{
		(*new)[*j] = s[*i];
		*i += 1;
		*j += 1;
	}
}

void	ft_cpy_double(char *s, char **new, int *i, int *j)
{
	*i += 1;
	while (s[*i] && s[*i] != '\"')
	{
		(*new)[*j] = s[*i];
		*i += 1;
		*j += 1;
	}
}

void	ft_cpy(char *s, char **new, int *i, int *j)
{
	while (s[*i] && s[*i] != '\'' && s[*i] != '\"')
	{
		(*new)[*j] = s[*i];
		*i += 1;
		*j += 1;
	}
}

char	*ft_erase_quotes(char *s, int size)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * ft_strlen(s) - size + 1);
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '\"' && s[i] != '\'')
			ft_cpy(s, &new, &i, &j);
		else if (s[i] == '\'')
			ft_cpy_simple(s, &new, &i, &j);
		else if (s[i] == '\"')
			ft_cpy_double(s, &new, &i, &j);
	}
	new[j] = '\0';
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
