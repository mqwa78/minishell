
#include "minishell.h"

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
		if ((s[i] == 44 || s[i] == 35) && !dq && !sq)
			return (1);
		else if ((s[i] == 38 || s[i] == 42 || s[i] == 33) && !dq && !sq)
			return (1);
		else if ((s[i] == 40 || s[i] == 41 || s[i] == 91) && !dq && !sq)
			return (1);
		else if ((s[i] == 93 || s[i] == 123 || s[i] == 125) && !dq && !sq)
			return (1);
		else if (s[i] == '?' && s[i - 1] && s[i - 1] != '$' && !dq && !sq)
			return (1);
	}
	return (0);
}

int	ft_only_spaces(char *s)
{
	int	i;

	i = 0;
	if (!s || !*s)
		return (1);
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_parse(t_data *data)
{	
	if (data->line[0] == '\0' || ft_only_spaces(data->line))
		return (ft_print_parse(data, 0));
	if (ft_open_quotes(data->line))
		return (ft_print_parse(data, 1));
	if (ft_invalid_char(data->line))
		return (ft_print_parse(data, 2));
	if (tokeniser(data, data->line))
		return (0);
	expander(data);
	if (!cmd_builder(data))
		return (0);
	return (1);
}
