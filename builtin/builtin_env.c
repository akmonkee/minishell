/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:53:22 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:53:22 by msisto           ###   ########.fr       */
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
