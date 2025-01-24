/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/01/24 12:45:55 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	doc_cmd(t_cmd *cmd)
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
		doc_cmd(pcmd->left);
		doc_cmd(pcmd->right);
	}
	else if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->here_doc == 0)
			return ;
		else
			here_doc(rcmd, rcmd->file);
	}
	return ;
}

void	runcmd(t_cmd *cmd, char	**envp)
{
	t_execcmd	*ecmd;

	if (!cmd)
	{
		write(2, "no parse tree\n", 14);
		exit (1);
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (!ecmd->argv[0])
		{
			write(2, "no args tree\n", 13);
			exit (1);
		}
		if (!ecmd->eargv[0])
			mtxs_free(ecmd->eargv);
		ft_execute_command(ecmd->argv, envp);
	}
	else if (cmd->type == PIPE)
		runpipe(cmd, envp);
	else if (cmd->type == REDIR)
		runredir(cmd, envp);
}
