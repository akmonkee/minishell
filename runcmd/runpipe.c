/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:59:25 by msisto            #+#    #+#             */
/*   Updated: 2025/03/18 13:01:54 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runpipe(t_pipecmd *pcmd, t_mini *mini)
{
	int	p[2];
	int	pid_left;
	int	pid_right;
	int	exit_status;

	pipe(p);
	pid_left = fork();
	if (pid_left == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, mini);
		mtxs_free(mini->env);
		free(mini);
		exit(g_exit_code);
	}
	pid_right = fork();
	if (pid_right == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, mini);
		mtxs_free(mini->env);
		free(mini);
		exit(g_exit_code);
	}
	close(p[0]);
	close(p[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	g_exit_code = WEXITSTATUS(exit_status);
}
