/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 11:57:08 by msisto            #+#    #+#             */
/*   Updated: 2024/12/20 12:10:19 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	runcmd(t_cmd *cmd)
{
	t_execcmd	*ecmd;

	if (cmd == 0)
	{
		write(2, "no parse tree\n", 14);
		return ;
	}
	ecmd = (t_execcmd *)cmd;
	if (ecmd->argv[0] == 0)
	{
		write(2, "no args tree\n", 13);
		return ;
	}
	execve(ecmd->argv[0], ecmd->argv, );
}
