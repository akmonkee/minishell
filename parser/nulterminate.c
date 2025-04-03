/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:55:37 by msisto            #+#    #+#             */
/*   Updated: 2025/04/03 16:21:00 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	rcmd_nullterminate(t_cmd *cmd)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	nulterminate(rcmd->cmd);
}

static void	pcmd_nullterminate(t_cmd *cmd)
{
	t_pipecmd	*pcmd;

	pcmd = (t_pipecmd *)cmd;
	nulterminate(pcmd->left);
	nulterminate(pcmd->right);
}

t_cmd	*nulterminate(t_cmd *cmd)
{
	int			i;
	t_execcmd	*ecmd;

	if (cmd == 0)
		return (0);
	i = 0;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		while (ecmd->argv[i])
		{
			*ecmd->eargv[i] = 0;
			i++;
		}
	}
	else if (cmd->type == REDIR)
		rcmd_nullterminate(cmd);
	else if (cmd->type == PIPE)
		pcmd_nullterminate(cmd);
	return (cmd);
}
