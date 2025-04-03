/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freecmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:30:33 by msisto            #+#    #+#             */
/*   Updated: 2025/04/03 16:23:55 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ffree(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	free(str);
}

void	mtxs_free(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		ffree(mtx[i]);
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
	}
}
