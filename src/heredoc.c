/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:18:48 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/17 21:09:34 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expand_spe_here(t_data *data, char *s, int i)
{
	char	*nb;
	char	*new;
	int		size;
	int		j;

	nb = ft_itoa(data->exit);
	if (!nb)
		ft_clear_spe_here(data, NULL);
	size = ft_strlen(s) + ft_strlen(nb) - SPE_SIZE;
	new = malloc(sizeof(char) * size + 1);
	if (!new)
		ft_clear_spe_here(data, nb);
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

char	*ft_expand_word_here(t_data *data, char *s, int i)
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
		ft_clear_expand_here(data, key, val, 0);
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
	ft_clear_expand_here(data, key, val, -1);
	return (ft_free_and_return(new, s));
}

void	ft_expand_here(t_data *data, char **str)
{
	char	*s;
	int		i;

	s = *str;
	i = -1;
	while (s[++i])
	{
		if (s[i] == '$' && s[i + 1] && ft_isalnum(s[i + 1]))
		{
			*str = ft_expand_word_here(data, *str, i + 1);
			s = *str;
			i = -1;
		}
		else if (s[i] == '$' && s[i + 1] && s[i + 1] == '?')
		{
			*str = ft_expand_spe_here(data, *str, i);
			s = *str;
			i = -1;
		}
	}
}

int	read_stdin(t_data *data, int fd, char *key)
{
	char	*buf;
	int		stdin_backup;

	stdin_backup = dup(STDIN_FILENO);
	init_signals_alt(data);
	while (1)
	{
		buf = readline("> ");
		if (!buf && g_sig_pid != 2)
		{
			print_here(key, fd, 0);
			break ;
		}
		if ((!buf && g_sig_pid == 2) || !ft_strlen(buf) || !ft_strcmp(key, buf))
			break ;
		ft_expand_here(data, &buf);
		print_here(buf, fd, 1);
		free(buf);
	}
	free(buf);
	close(fd);
	init_signals(data);
	dup2(stdin_backup, STDIN_FILENO);
	return (1);
}

int	open_here(t_data *data, char *key)
{
	int	fd;

	fd = open(HERENAME, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_stdin(data, fd, key))
	{
		unlink(HERENAME);
		return (-1);
	}
	fd = open(HERENAME, O_RDONLY);
	if (fd > 0)
		unlink(HERENAME);
	return (fd);
}
