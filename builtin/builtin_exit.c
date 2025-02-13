/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:53:31 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:53:31 by msisto           ###   ########.fr       */
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
	return (0);
}
