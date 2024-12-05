/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:06:29 by efoschi           #+#    #+#             */
/*   Updated: 2024/12/05 15:08:47 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//devo gestire l'execute dei vari comandi della shell
void	execute(t_cmd *cmd)
{
	if (cmd->type == EXEC)
	{
		//eseguo il comando
	}
	else if (cmd->type == REDIR)
	{
		//gestisco i redirect
	}
	else if (cmd->type == PIPE)
	{
		//gestisco i pipe
	}
	else if (cmd->type == LIST)
	{
		//gestisco i comandi in lista
	}
	else if (cmd->type == BACK)
	{
		//gestisco i comandi in background
	}
}
