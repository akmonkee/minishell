/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:55:37 by msisto            #+#    #+#             */
/*   Updated: 2025/01/17 11:07:28 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*nulterminate(t_cmd *cmd)
{
	int	i;
	t_execcmd	*ecmd;
	t_pipecmd	*pcmd;
	t_redircmd	*rcmd;

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
	else if(cmd->type == REDIR)
	{
		rcmd = (t_redircmd *)cmd;
		nulterminate(rcmd->cmd);
	}
	else if(cmd->type == PIPE)
	{
		pcmd = (t_pipecmd *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}
	return (cmd);
}
