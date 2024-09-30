
#include "minishell.h"

int	is_special(char *s, char c, int i)
{	
	if (c == '<' && s[i + 1] && s[i + 1] == '<')
		return (HEREDOC);
	else if (c == '>' && s[i + 1] && s[i + 1] == '>')
		return (APPEND);
	else if (c == '<')
		return (INPUT);
	else if (c == '>')
		return (TRUNC);
	else if (c == '|')
		return (PIPE);
	return (0);
}

int	ft_count_len(char *s, int i)
{	
	int	count;
	int	sq;
	int	dq;

	count = 0;
	sq = 0;
	dq = 0;
	while (s[i])
	{
		ft_quote(s[i], &dq, &sq);
		count++;
		i++;
		if (s[i] && !dq && !sq && (ft_isspace(s[i]) || is_special(s, s[i], i)))
			return (count);
	}
	return (count);
}

int	ft_add_token(t_tok **tok, char *s, int *i)
{	
	char	*tmp;
	int		j;
	int		k;

	j = ft_count_len(s, *i);
	tmp = malloc(sizeof(char) * j + 1);
	if (!tmp)
		return (0);
	k = 0;
	while (j-- > 0)
	{
		tmp[k] = s[*i];
		k++;
		*i += 1;
	}
	tmp[k] = '\0';
	if (!ft_create_token(tok, tmp, ARG))
	{
		ft_clear_tok(tok);
		return (0);
	}
	return (1);
}

int	ft_add_special(t_tok **tok, char *s, int *i)
{	
	int	spe;

	spe = is_special(s, s[*i], *i);
	if (spe == INPUT || spe == TRUNC || spe == PIPE)
	{
		if (spe == INPUT && !ft_create_spe(tok, "<", INPUT))
			return (0);
		else if (spe == TRUNC && !ft_create_spe(tok, ">", TRUNC))
			return (0);
		else if (spe == PIPE && !ft_create_spe(tok, "|", PIPE))
			return (0);
		*i += 1;
	}
	else
	{
		if (spe == HEREDOC && !ft_create_spe(tok, "<<", HEREDOC))
			return (0);
		else if (spe == APPEND && !ft_create_spe(tok, ">>", APPEND))
			return (0);
		*i += 2;
	}
	return (1);
}

int	tokeniser(char *s)
{
	t_tok	*token;
	t_tok	*cur;
	int		i;

	token = NULL;
	i = 0;
	while (s[i])
	{	
		while (ft_isspace(s[i]))
			i++;
		if (s[i] && !is_special(s, s[i], i) && !ft_add_token(&token, s, &i))
		{	
			ft_clear_tok(&token);
			return (1);
		}
		if (s[i] && is_special(s, s[i], i) && !ft_add_special(&token, s, &i))
		{
			ft_clear_tok(&token);
			return (1);
		}
	}
	cur = token;
	while (token->next)
	{
		printf("%s\n", token->token);
		printf("%d\n", token->type);
		token = token->next;
	}
	printf("%s\n", token->token);
	printf("%d\n", token->type);
	while (token)
	{
		printf("%s\n", token->token);
		token = token->prev;
	}
	ft_clear_tok(&cur);
	return (0);
}

int	main(void)
{	
	char	*str;
	int		i;

	str = "echo bonjour >> file.txt | cat << file.txt |";
	i = tokeniser(str);
	return (0);
}