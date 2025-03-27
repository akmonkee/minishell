/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/03/25 10:34:58 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runcmd(t_cmd *cmd, t_mini *mini)
{
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;

	if (!cmd)
	{
		perror("no parse tree\n");
		return ;
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (!ecmd->argv[0])
		{
			perror("no args for tree\n");
			return ;
		}
		if (!ecmd->eargv[0])
			mtxs_free(ecmd->eargv);
		ft_execute_command(ecmd->argv, mini);
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		runpipe(pcmd, mini);
	}
	else if (cmd->type == REDIR)
		runredir(cmd, mini);
}
