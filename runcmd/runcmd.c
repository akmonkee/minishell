/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/02/10 11:54:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runcmd(t_cmd *cmd, char	**envp)
{
	t_execcmd	*ecmd;


	if (cmd->type == EXEC)
	{
		t_execcmd *ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0])
		exit (0);
	}
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
