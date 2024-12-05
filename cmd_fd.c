
#include "minishell.h"

int	open_file(char *filename, int type)
{
	int	fd;

	fd = -2;
	if (type == INPUT)
		fd = open(filename, O_RDONLY, 0644);
	else if (type == TRUNC)
		fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
		perror(filename);
	return (fd);
}

int	get_out(t_cmd **elem, t_tok *tok)
{
	if (tok->type == APPEND)
	{
		if ((*elem)->out >= 0)
			close((*elem)->out);
		(*elem)->out = open_file(tok->next->token, APPEND);
		if ((*elem)->out == -1)
			return (0);
	}
	else if (tok->type == TRUNC)
	{
		if ((*elem)->out >= 0)
			close((*elem)->out);
		(*elem)->out = open_file(tok->next->token, TRUNC);
		if ((*elem)->out == -1)
			return (0);
	}
	return (1);
}

int	get_in(t_cmd **elem, t_tok *tok)
{
	if (tok->type == INPUT)
	{
		if ((*elem)->in >= 0)
			close((*elem)->in);
		(*elem)->in = open_file(tok->next->token, INPUT);
		if ((*elem)->in == -1)
			return (0);
	}
	return (1);
}

int	ft_get_files(t_cmd **elem, t_tok *token)
{
	t_tok	*cur;

	cur = token;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == INPUT || cur->type == HEREDOC)
		{
			if (!get_in(elem, cur))
				return (0);
		}
		else if (cur->type == APPEND || cur->type == TRUNC)
		{
			if (!get_out(elem, cur))
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}
