
#include "minishell.h"

// '\'' ascii = 39
// '\"' ascii = 34
// On passe sq et dq a 1 si on est dans des quotes
// On repasse sq et dq a 0 quand on sort des quotes
// si a la fin sq == 1 ou dq == 1 alors open quote

int	ft_open_quotes(char *s)
{	
	int	sq;
	int	dq;
	int	i;

	sq = 0;
	dq = 0;
	i = -1;
	while (s[++i])
	{
		if (s[i] == 34 && !dq && !sq)
			dq = 1;
		else if (s[i] == 39 && !sq && !dq)
			sq = 1;
		else if (s[i] == 34 && dq)
			dq = 0;
		else if (s[i] == 39 && sq)
			sq = 0;
	}
	if (sq || dq)
		return (1);
	return (0);
}

void	ft_quote(char c, int *dq, int *sq)
{
	if (c == 34 && !*dq && !*sq)
		*dq = 1;
	else if (c == 39 && !*sq && !*dq)
		*sq = 1;
	else if (c == 34 && *dq)
		*dq = 0;
	else if (c == 39 && *sq)
		*sq = 0;
}

// Minishell ne doit pas gérer tous les char spéciaux.
// On check si il y a un char spé invalid sans être dans des quotes.

int	ft_invalid_char(char *s)
{	
	int	i;
	int	dq;
	int	sq;

	i = -1;
	dq = 0;
	sq = 0;
	while (s[++i])
	{
		ft_quote(s[i], &dq, &sq);
		if ((s[i] == 44 || s[i] == 126 || s[i] == 35) && !dq && !sq)
			return (1);
		else if ((s[i] == 38 || s[i] == 42 || s[i] == 33) && !dq && !sq)
			return (1);
		else if ((s[i] == 40 || s[i] == 41 || s[i] == 91) && !dq && !sq)
			return (1);
		else if ((s[i] == 93 || s[i] == 123 || s[i] == 125) && !dq && !sq)
			return (1);
		else if (s[i] == 59 && !dq && !sq)
			return (1);
		else if (s[i] == '?' && s[i - 1] && s[i - 1] != '$' && !dq && !sq)
			return (1);
	}
	return (0);
}

// free data->line si error
//add tokeniser ? et ensuite check tok syntax puis continu si pb
//Si fail tokeniser, free all, env compris car malloc fail 

int	ft_parse(t_data *data)
{	
	if (data->line[0] == '\0')
		return (0);
	if (ft_open_quotes(data->line))
		return (ft_print_parse(data, 1));
	if (ft_invalid_char(data->line))
		return (ft_print_parse(data, 2));
	if (tokeniser(data, data->line))
		return (0);
	expander(data);
	return (1);
}
