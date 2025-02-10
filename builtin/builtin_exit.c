/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:14:25 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 16:14:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(char *input)
{
	char	**var;
	int		n;

	n = 0;
	var = ft_split(input, ' ', 0, 0);
	if (var[1] != NULL)
	{
		n = ft_atoi(var[1]);
		g_exit_code = (unsigned char)n;
	}
	mtxs_free(var);
	exit(g_exit_code);
}
