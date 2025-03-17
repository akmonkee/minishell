/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/03/17 13:35:18 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	doc_cmd(t_cmd *cmd, char **envp)
{
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

	if (!cmd)
	{
		write(2, "no parse tree\n", 14);
		exit (1);
	}
	if (cmd->type == EXEC)
	{
		return ;
	}
	else if (cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		doc_cmd(pcmd->left, envp);
		doc_cmd(pcmd->right, envp);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->here_doc == 1)
			here_doc(rcmd, rcmd->file);
	}
}

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
