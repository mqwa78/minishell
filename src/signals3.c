/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:52:40 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/17 20:42:01 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint_parent_alt(int sig)
{
	g_sig_pid = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_redisplay();
	close(STDIN_FILENO);
}

void	handle_sigquit_parent_alt(int sig)
{
	g_sig_pid = sig;
}

void	handle_signals_parent_alt(int sig)
{
	if (sig == SIGINT)
		handle_sigint_parent_alt(sig);
	else if (sig == SIGQUIT)
		handle_sigquit_parent_alt(sig);
}

int	init_signals_alt(t_data *data)
{
	struct sigaction	action;
	struct sigaction	ignore_action;

	(void)data;
	ft_memset(&action, 0, sizeof(action));
	action.sa_handler = handle_signals_parent_alt;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	if (sigaction(SIGINT, &action, NULL) == -1)
		perror("Failed to set SIGINT handler");
	ft_memset(&ignore_action, 0, sizeof(ignore_action));
	ignore_action.sa_handler = SIG_IGN;
	sigemptyset(&ignore_action.sa_mask);
	ignore_action.sa_flags = 0;
	if (sigaction(SIGQUIT, &ignore_action, NULL) == -1)
		perror("Failed to ignore SIGQUIT");
	if (sigaction(SIGTSTP, &ignore_action, NULL) == -1)
		perror("Failed to ignore SIGTSTP");
	return (0);
}
