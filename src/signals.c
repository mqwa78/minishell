/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mqwa <mqwa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:49:01 by mqwa              #+#    #+#             */
/*   Updated: 2024/12/18 02:19:27 by mqwa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_prompt(int sig)
{
	(void)sig;
	g_sig_pid = 130;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 0);
}

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
	write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_sig_pid = 131;
}

void	signals2(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	setup_signal_handlers(int sig)
{
	if (sig == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (sig == 1)
	{
		signal(SIGINT, double_prompt);
		signal(SIGQUIT, handle_sigquit);
	}
}
