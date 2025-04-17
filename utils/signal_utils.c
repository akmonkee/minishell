/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:37:45 by msisto            #+#    #+#             */
/*   Updated: 2025/04/17 11:42:33 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ign(int sig)
{
	if (sig)
		return ;
}

void	signal_execve(int sig)
{
	if (sig == SIGINT)
		g_exit_code = 130;
	if (sig == SIGQUIT)
		g_exit_code = 131;
	exit(g_exit_code);
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
		exit(1);
}

void	pexe_exit_status(int exit_status)
{
	if (WIFEXITED(exit_status))
		g_exit_code = WEXITSTATUS(exit_status);
	else if (WIFSIGNALED(exit_status))
		g_exit_code = 128 + WTERMSIG(exit_status);
}
