/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/05/19 10:44:32 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_heredoc(t_cmd *cmd, t_mini *mini)
{
	t_redircmd	*rcmd;
	t_pipecmd	*pcmd;

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
		pcmd = (t_pipecmd *)cmd;
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

static void	pexe_ll(char *input, t_mini *mini)
{
	pid_t		pid;
	int			exit_status;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, ign);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, signal_execve);
		signal(SIGQUIT, signal_execve);
		run_heredoc(mini->cmd, mini);
		runcmd(mini->cmd, mini);
		free_mini(mini);
		exit(0);
	}
	else
	{
		waitpid(pid, &exit_status, 0);
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
		pexe_exit_status(exit_status);
	}
}

void	parse_exe(char *input, t_mini *mini)
{
	t_execcmd	*ecmd;

	mini->cmd = parsecmd(input);
	if (!mini->cmd)
		return ;
	g_exit_code = 0;
	ecmd = (t_execcmd *)mini->cmd;
	if (mini->cmd && mini->cmd->type == EXEC && control_bt(ecmd->argv[0]))
		runcmd(mini->cmd, mini);
	else if (mini->cmd)
		pexe_ll(input, mini);
	freecmd(mini->cmd);
	free(mini->cmd);
}
