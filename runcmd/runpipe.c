/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:59:25 by msisto            #+#    #+#             */
/*   Updated: 2025/03/14 12:32:39 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork1()
{
	int	pid;

	pid = fork();
	return (pid);
}

void	left_pipe(t_pipecmd *pcmd, char **envp, int p_0, int p_1)
{
	close(1);
	dup(p_1);
	close(p_0);
	close(p_1);
	runcmd(pcmd->left, envp);
}

void	right_pipe(t_pipecmd *pcmd, char **envp, int p_0, int p_1)
{
	close(0);
	dup(p_0);
	close(p_0);
	close(p_1);
	runcmd(pcmd->right, envp);
}

void	runpipe(t_cmd *cmd, char **envp)
{
	int			p[2];
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
	{
		perror("pipe\n");
		return ;
	}
	if (fork1() == 0)
		left_pipe(pcmd, envp, p[0], p[1]);
	if (fork1() == 0)
		right_pipe(pcmd, envp, p[0], p[1]);
	close(p[0]);
	close(p[1]);
	wait(NULL);
	wait(NULL);
}
