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

int	builtin_env(char **env, int print, t_execcmd *cmd)
{
	int		i;
	char	**str;

	i = 0;
	while (env[i] && print == 1)
	{
		str = ft_split(env[i], '=');
		if (str[0] && str[1])
			printf(%s\n, env[i]);
		free_matrix(str);
		i++;
	}
	return (1);
}

void	env2(char **env)
{
	int		i;
	char	**str;
	char	**matrix;

	i = 0;
	matrix = order(copy_matrix(env), 0, 0, ft_matrixlen(env));
	while (matrix[i])
	{
		str = ft_split(matrix[i], '=');
		if (ft_matrixlen(str) == 1)
			printf("declare -x %s\n", str[0]);
		else
			printf("declare -x %s=\"%s\"\n", str[0], str[1]);
		free_matrix(str);
		i++;
	}
	free_matrix(matrix);
}
