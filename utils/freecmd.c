/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:30:33 by msisto            #+#    #+#             */
/*   Updated: 2025/04/15 14:10:34 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mini(t_mini *mini)
{
	free(mini->input);
	freecmd(mini->cmd);
	free(mini->cmd);
	mtxs_free(mini->env);
	free(mini);
}

void	no_path(char *cmd, t_mini *mini)
{
	char	*cp_cmd;

	cp_cmd = var_ex(cmd, '\0');
	free_mini(mini);
	panic_fun(cp_cmd, ": No such file or directory\n", 1, 1);
}

void	mtxs_free(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

void	freepipe(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	freecmd(pcmd->left);
	free(pcmd->left);
	freecmd(pcmd->right);
	free(pcmd->right);
}

void	freecmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;
	t_redircmd	*rcmd;

	if (cmd->type == 0)
		return ;
	if (cmd->type == PIPE)
		freepipe(cmd);
	if (cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (rcmd->file)
			free(rcmd->file);
		freecmd(rcmd->cmd);
		free(rcmd->cmd);
		if (rcmd->here_doc_name != NULL)
			free(rcmd->here_doc_name);
	}
}
