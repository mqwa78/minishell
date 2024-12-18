/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:47:57 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/18 21:34:18 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_data *data, t_tok *tok, int type)
{
	int	fd;

	fd = -2;
	if (!tok->token || !tok->token[0])
		return (-1);
	if (type == INPUT)
		fd = open(tok->token, O_RDONLY, 0644);
	else if (type == HEREDOC)
		fd = open_here(data, tok);
	else if (type == TRUNC)
		fd = open(tok->token, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(tok->token, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (type != HEREDOC && fd < 0)
	{
		write(2, "Minishell: ", 12);
		perror(tok->token);
	}
	return (fd);
}

int	get_out(t_data *data, t_cmd **elem, t_tok *tok)
{
	if (tok->type == APPEND)
	{
		if ((*elem)->out >= 0)
			close((*elem)->out);
		(*elem)->out = open_file(data, tok->next, APPEND);
		if ((*elem)->out == -1)
			return (0);
	}
	else if (tok->type == TRUNC)
	{
		if ((*elem)->out >= 0)
			close((*elem)->out);
		(*elem)->out = open_file(data, tok->next, TRUNC);
		if ((*elem)->out == -1)
			return (0);
	}
	return (1);
}

int	get_in(t_data *data, t_cmd **elem, t_tok *tok)
{
	if (tok->type == INPUT)
	{
		if ((*elem)->in >= 0)
			close((*elem)->in);
		(*elem)->in = open_file(data, tok->next, INPUT);
		if ((*elem)->in == -1)
			return (0);
	}
	else if (tok->type == HEREDOC)
	{
		if ((*elem)->in >= 0)
			close((*elem)->in);
		(*elem)->in = open_file(data, tok->next, HEREDOC);
		if ((*elem)->in == -1)
			return (0);
	}
	return (1);
}

int	ft_get_files(t_data *data, t_cmd **elem, t_tok *token)
{
	t_tok	*cur;

	cur = token;
	while (cur && cur->type != PIPE)
	{
		if (cur->type == INPUT || cur->type == HEREDOC)
		{
			if (!get_in(data, elem, cur))
				return (0);
		}
		else if (cur->type == APPEND || cur->type == TRUNC)
		{
			if (!get_out(data, elem, cur))
				return (0);
		}
		cur = cur->next;
	}
	return (1);
}
