/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:37:45 by msisto            #+#    #+#             */
/*   Updated: 2025/03/14 17:35:00 by msisto           ###   ########.fr       */
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
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = EXIT_FAILURE;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGTERM)
		exit(1);
	else if (sig == SIGQUIT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
