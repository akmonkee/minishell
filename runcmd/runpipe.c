/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:59:25 by msisto            #+#    #+#             */
/*   Updated: 2025/03/17 13:46:53 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	left_pipe(t_pipecmd *pcmd, t_mini *mini, int p_0, int p_1)
{
	close(1);
	dup(p_1);
	close(p_0);
	close(p_1);
	runcmd(pcmd->left, mini);
}

void	right_pipe(t_pipecmd *pcmd, t_mini *mini, int p_0, int p_1)
{
	close(0);
	dup(p_0);
	close(p_0);
	close(p_1);
	runcmd(pcmd->right, mini);
}

void	runpipe(t_pipecmd *pcmd, t_mini *mini)
{
	int	p[2];
	int	pid_left;
	int	pid_right;
	int	exit_status;

	if (pipe(p) < 0)
	{
		perror("pipe\n");
		return ;
	}
	pid_left = fork();
	if (pid_left == 0)
		left_pipe(pcmd, mini, p[0], p[1]);
	pid_right = fork();
	if (pid_right == 0)
		right_pipe(pcmd, mini, p[0], p[1]);
	close(p[0]);
	close(p[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	g_exit_code = WEXITSTATUS(exit_status);
}
