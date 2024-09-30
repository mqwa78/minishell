
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

int	ft_check_spe(char *s, char c, int i)
{	
	int	count_c;

	count_c = 1;
	while (s[++i] && (s[i] == c || ft_isspace(s[i])))
	{	
		if (s[i] == c)
			count_c++;
	}
	if (count_c > 2)
		return (ft_print_error_syn(c));
	return (0);
}

int	ft_check_syntax(char *s)
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
		if (s[i] == '<' && !dq && !sq && ft_check_spe(s, s[i], i))
			return (1);
		else if (s[i] == '>' && !dq && !sq && ft_check_spe(s, s[i], i))
			return (1);
	}
	return (0);
}

int	ft_parse(char *str)
{	
	if (ft_open_quotes(str))
		return (ft_print_parse(1));
	if (ft_invalid_char(str))
		return (ft_print_parse(2));
	if (ft_check_syntax(str))
		return (ft_print_parse(0));
	return (1);
}

/*int	main(void)
{	
	char	*str;

	//str = "\"bonjo \'ur \"  \' \"\" ";
	str = "echo bonjour \"*\" | ls -la | echo yo >> >file";
	printf("%s\n", str);
	printf("%d\n", ft_parse(str));
	return (0);
}*/