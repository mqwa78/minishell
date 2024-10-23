
#include "minishell.h"

void	ft_clear_quote(t_data *data, t_tok **tok)
{
	char	*s;
	int		count;

	s = (*tok)->token;
	count = ft_count_quotes(s);
	if (count == 0)
		return ;
	(*tok)->token = ft_erase_quotes((*tok)->token, count); 
	if (!(*tok)->token)
		ft_clear_garbage(data, -1);
}

char	*ft_expand_word(t_data *data, char *s, int i)
{
	char	*key;
	char	*val;
	char	*new;
	int		tmp;
	int		j;

	key = ft_get_key(data, s, i);
	val = ft_get_value(data, key);
	tmp = ft_strlen(s) + ft_strlen(val) - (ft_strlen(key) + 1);
	new = malloc(sizeof(char) * (tmp + 1));
	if (!new)
		ft_clear_expand(data, key, val, 0);
	tmp = -1;
	j = -1;
	while (s[++tmp] && tmp < i - 1)
		new[++j] = s[tmp];
	i = -1;
	while (val[++i])
		new[++j] = val[i];
	tmp += ft_strlen(key);
	while (s[++tmp])
		new[++j] = s[tmp];
	new[++j] = '\0';
	ft_clear_expand(data, key, val, -1);
	return (ft_free_and_return(new, s));
}

char	*ft_expand_spe(t_data *data, char *s, int i)
{
	char	*nb;
	char	*new;
	int		size;
	int		j;

	nb = ft_itoa(data->spe);
	if (!nb)
		ft_clear_garbage(data, -1);
	size = ft_strlen(s) + ft_strlen(nb) - SPE_SIZE;
	new = malloc(sizeof(char) * size + 1);
	if (!new)
		ft_clear_expand(data, nb, NULL, 2);
	j = -1;
	size = -1;
	while (s[++j] && j < i)
		new[++size] = s[j];
	i = -1;
	while (nb[++i])
		new[++size] = nb[i];
	j += SPE_SIZE - 1;
	while (s[++j])
		new[++size] = s[j];
	new[++size] = '\0';
	free(nb);
	return (ft_free_and_return(new, s));
}

void	ft_expand(t_data *data, t_tok **tok)
{
	char	*s;
	int		i;
	int		dq;
	int		sq;

	s = (*tok)->token;
	dq = 0;
	sq = 0;
	i = -1;
	while (s[++i])
	{	
		ft_quote(s[i], &dq, &sq);
		if (s[i] == '$' && s[i + 1] && ft_isalnum(s[i + 1]) && !sq)
		{
			(*tok)->token = ft_expand_word(data, (*tok)->token, i + 1);
			s = (*tok)->token;
			i = -1;
		}
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?' && !sq)
		{
			(*tok)->token = ft_expand_spe(data, (*tok)->token, i);
			s = (*tok)->token;
			i = -1;
		}
	}
}

void	expander(t_data *data)
{	
	t_tok	*cur;

	cur = data->tok;
	while (cur)
	{	
		if (cur->type > 5)
		{
			ft_expand(data, &cur);
			ft_clear_quote(data, &cur);
		}
		cur = cur->next;
	}
}