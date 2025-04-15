/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/04/15 13:30:02 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_heredoc(t_cmd *cmd, t_mini *mini)
{
	t_redircmd	*rcmd;

	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->here_doc == 1)
		{
			rcmd->here_doc_name = var_content_elab(rcmd->file, mini->env);
			handle_heredoc(rcmd, rcmd->here_doc_name, mini);
		}
		run_heredoc(rcmd->cmd, mini);
	}
	else if (cmd->type == PIPE)
	{
		t_pipecmd *pcmd = (t_pipecmd *)cmd;
		run_heredoc(pcmd->left, mini);
		run_heredoc(pcmd->right, mini);
	}
}

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
