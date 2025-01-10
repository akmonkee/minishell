/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runpipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:59:25 by msisto            #+#    #+#             */
/*   Updated: 2025/01/10 12:18:06 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork1()
{
	int	pid;

	pid = fork();
	return (pid);
}

void	runpipe(t_cmd *cmd, char **envp)
{
	int			p[2];
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	if (pipe(p) < 0)
	{
		write(2, "pipe\n", 5);
		return ;
	}
	if (fork1() == 0)
	{
		close(1);
		dup(p[1]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->left, envp);
	}
	if (fork1() == 0)
	{
		close(0);
		dup(p[0]);
		close(p[0]);
		close(p[1]);
		runcmd(pcmd->right, envp);
	}
	close(p[0]);
	close(p[1]);
	wait(NULL);
	wait(NULL);
}
