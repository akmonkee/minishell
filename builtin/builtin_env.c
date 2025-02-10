/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:49:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 15:49:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(char **env, int flag)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (flag == 1)
			printf("declare -x ");
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
