/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:51:07 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 16:51:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	malloc_p(char **m)
{
	if (m == NULL)
	{
		return (0);
		perror("Panic: Malloc error");
		exit(EXIT_FAILURE);
	}
	return (1);
}
