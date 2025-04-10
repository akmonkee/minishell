/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/04/10 11:25:08 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	rcmd_exec(t_cmd *cmd, t_mini *mini)
{
	t_execcmd	*ecmd;

	ecmd = (t_execcmd *)cmd;
	if (!ecmd->argv[0])
	{
		panic_fun("no args ", "for tree\n", 1, 0);
		return ;
	}
	if (!ecmd->eargv[0])
		mtxs_free(ecmd->eargv);
	ft_execute_command(ecmd->argv, mini);
}

void	runcmd(t_cmd *cmd, t_mini *mini)
{
	t_pipecmd	*pcmd;

	if (!cmd)
	{
		panic_fun("no parse ", "tree\n", 1, 0);
		return ;
	}
	if (cmd->type == EXEC)
		rcmd_exec(cmd, mini);
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		runpipe(pcmd, mini);
	}
	else if (cmd->type == REDIR)
		runredir(cmd, mini);
}
