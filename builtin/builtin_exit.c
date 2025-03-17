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

void	builtin_exit(char **input)
{
	int	n;

	n = 0;
	if (mtx_len(input) > 2)
	{
		g_exit_code = 2;
		return ;
	}
	if (input[1] != NULL)
	{
		n = ft_atoi(input[1]);
		g_exit_code = (unsigned char)n;
	}
	exit(g_exit_code);
}
