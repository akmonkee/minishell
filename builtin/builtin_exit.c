/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:59:13 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:59:13 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_exit(char **input, t_mini *mini)
{
	int	i;

	i = -1;
	if (mtx_len(input) > 2)
	{
		g_exit_code = 2;
		return ;
	}
	if (input[1] != NULL)
	{
		while (input[1][++i])
		{
			if (!ft_isdigit(input[1][i]))
			{
				panic_fun("exit: ", input[1], 2, 0);
				panic_fun("numeric", " arg required", 2, 0);
				return ;
			}
		}
		g_exit_code = (unsigned char)ft_atoi(input[1]);
	}
	free_mini(mini);
	exit(g_exit_code);
}
