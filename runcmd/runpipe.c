/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:59:25 by msisto            #+#    #+#             */
/*   Updated: 2025/04/03 16:13:12 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pipe_side(t_pipecmd *pcmd, int *p, int channel, t_mini *mini)
{
	close(channel);
	dup(p[channel]);
	close(p[0]);
	close(p[1]);
	if (channel == 1)
		runcmd(pcmd->left, mini);
	else
		runcmd(pcmd->right, mini);
	freecmd(mini->cmd);
	free(mini->cmd);
	mtxs_free(mini->env);
	free(mini);
	exit(g_exit_code);
}

void	runpipe(t_pipecmd *pcmd, t_mini *mini)
{
	int	p[2];
	int	pid_left;
	int	pid_right;
	int	exit_status;

	pipe(p);
	pid_left = fork();
	if (pid_left == 0)
		pipe_side(pcmd, p, 1, mini);
	pid_right = fork();
	if (pid_right == 0)
		pipe_side(pcmd, p, 0, mini);
	close(p[0]);
	close(p[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	g_exit_code = WEXITSTATUS(exit_status);
}
