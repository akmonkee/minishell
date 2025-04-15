/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:37:45 by msisto            #+#    #+#             */
/*   Updated: 2025/04/15 09:46:11 by msisto           ###   ########.fr       */
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
