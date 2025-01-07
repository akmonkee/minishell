/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2025/01/07 10:21:02 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cmd_free(t_cmd *cmd)
{
	int	i;
	t_execcmd	*ecmd;

	i = 0;
	if (!cmd)
		return ;
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		mtxs_free(ecmd->argv);
		mtxs_free(ecmd->eargv);
		free(ecmd);
	}
}

void	runcmd(t_cmd *cmd, char	**envp)
{
	t_execcmd	*ecmd;
	int	i = 0;

	if (cmd == 0)
	{
		write(2, "no parse tree\n", 14);
		return ;
	}
	if (cmd->type == EXEC)
	{
		ecmd = (t_execcmd *)cmd;
		if (ecmd->argv[0] == 0)
		{
			write(2, "no args tree\n", 13);
			return ;
		}
		ft_execute_command(ecmd->argv, envp);
	}
}
