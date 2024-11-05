
#include "minishell.h"

void	ft_setup_token_types(t_tok *tok)
{
	t_tok	*cur;
	int		cmd;

	cur = tok;
	while (cur)
	{	
		if (cur->type > 0 && cur->type < 5 && cur->next)
			cur->next->type = FILE;
		cur = cur->next;
	}
	cur = tok;
	cmd = 1;
	while (cur)
	{
		if (cur->type == ARG && cmd)
		{
			cur->type = CMD;
			cmd = 0;
		}
		else if (cur->type == PIPE)
			cmd = 1;
		cur = cur->next;
	}
}

int	ft_check_pipe(t_tok *tok)
{
	if (!tok->prev)
	{
		ft_putstr_fd("Minishell : syntax error near ", 2);
		ft_putstr_fd("unexpected token `|\'\n", 2);
		return (1);
	}
	if (!tok->next)
	{
		ft_putstr_fd("Minishell : error open pipe\n", 2);
		return (1);
	}
	if (tok->next->type == PIPE)
	{
		ft_putstr_fd("Minishell : error double pipe\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_spe_synthax(t_tok *tok)
{
	if (!tok->next)
	{
		ft_putstr_fd("Minishell : syntax error near ", 2);
		ft_putstr_fd("unexpected token `newline\'\n", 2);
		return (1);
	}
	if (tok->next->type > 0 && tok->next->type < 6)
	{
		ft_putstr_fd("Minishell : syntax error near ", 2);
		ft_putstr_fd("unexpected token `", 2);
		ft_putstr_fd(tok->next->token, 2);
		ft_putstr_fd("\'\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_synthax_token(t_tok *tok)
{
	while (tok)
	{
		if (tok->type == PIPE)
		{
			if (ft_check_pipe(tok))
				return (1);
		}
		else if (tok->type > 0 && tok->type < 5)
		{
			if (ft_check_spe_synthax(tok))
				return (1);
		}
		tok = tok->next;
	}
	return (0);
}
