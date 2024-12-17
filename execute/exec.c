/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:06:29 by efoschi           #+#    #+#             */
/*   Updated: 2024/12/17 16:24:38 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//devo gestire l'execute dei vari comandi della shell
void	execute(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		execute_cmd((t_execcmd *)cmd);
	}
	else if (cmd->type == REDIR)
	{
		redircmd((t_redircmd *)cmd);
	}
	else if (cmd->type == PIPE)
	{
		pipecmd((t_pipecmd *)cmd);
	}
	else if (cmd->type == LIST)
	{
		listcmd((t_listcmd *)cmd);
	}
	else if (cmd->type == BACK)
	{
		backcmd((t_back_cmd *)cmd);
	}
	else
		perror("cmd type");
}
