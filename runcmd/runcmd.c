/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/01/08 12:08:41 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runcmd(t_cmd *cmd, char	**envp)
{
	int	p[2];
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;

	if (cmd == 0)
	{
		write(2, "no parse tree\n", 14);
		return ;
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
		{
			write(2, "no args tree\n", 13);
			return ;
		}
		ft_execute_command(ecmd->argv, envp);
	}
	if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;

		if (fork1() == 0)
		{
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left, envp);
		}
		if (fork1() == 0)
		{
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
}
