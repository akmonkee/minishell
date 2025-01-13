/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/01/13 15:26:46 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runcmd(t_cmd *cmd, char	**envp)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	if (cmd == 0)
	{
		write(2, "no parse tree\n", 14);
		return ;
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (!ecmd->argv[0])
		{
			write(2, "no args tree\n", 13);
			return ;
		}
		if (!ecmd->eargv[0])
			mtxs_free(ecmd->eargv);
		ft_execute_command(ecmd->argv, envp);
	}
	else if (cmd->type == PIPE)
		runpipe(cmd, envp);
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->mode == O_RDONLY)
			close(0);
		else if (rcmd->mode == O_WRONLY|O_CREAT|O_TRUNC)
			close(1);
		if (open(rcmd->file, rcmd->mode, 0777) < 0)
		{
			write (2, "Error\n open failed\n", 19);
			return ;
		}
		runcmd(rcmd->cmd, envp);
	}
}
