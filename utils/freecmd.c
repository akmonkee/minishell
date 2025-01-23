/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:30:33 by msisto            #+#    #+#             */
/*   Updated: 2025/01/22 10:46:02 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	t_redircmd	*rcmd;

	if (cmd->type == 0)
		return ;
	if (cmd->type == PIPE)
		freepipe(cmd);
	if(cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		if (&rcmd->file)
			free(rcmd->file);
		freecmd(rcmd->cmd);
		free(rcmd->cmd);
	}
}
