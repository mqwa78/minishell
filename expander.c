
#include "minishell.h"

/*void	ft_clear_quote(t_data *data, t_tok **tok)
{
	return ;
}*/

//Faire en sorte de ne jamais return NULL, soit return string, soit error donc free + exit
//use tmp comme index apres alvoir use comme size

char	*ft_expand_word(t_data *data, char *s, int i)
{
	char	*key;
	char	*val;
	char	*new;
	int		tmp;

	key = ft_get_key(data, s, i);
	val = ft_get_value(data, key);
	tmp = ft_strlen(s) + ft_strlen(val) - (ft_strlen(key) + 1);
	new = malloc(sizeof(char) * (tmp + 1));
	//if (!new)
		//ft_clear_garbage(data);
	//free(val);
	//free(s);
	return (new);
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
		//else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?' && !sq)
		//{
		//	ft_expand_spe();
		//s = (*tok)->token;
		//	i = -1;
		//}
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
			//ft_clear_quote(data, &cur);
		}
		cur = cur->next;
	}
}