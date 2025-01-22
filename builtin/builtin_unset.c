/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:38:06 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 16:38:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_unset(char **env, t_cmd *cur, char *str)
{
	int		i;
	int		j;
	char	**arg;
	char	**matrix;
	char	**matrix2;

	i = -1;
	j = 0;
	arg = take_args(cur, cur->cmd);
	if (malloc_p(arg) == 1 && ft_matrixlen(arg) > 1 && looking_for_env(env, str) != 0)
	{
		matrix2 = malloc((ft_matrixlen(env)) * sizeof(char *));
		malloc_p(matrix2);
		while (env[++j] != NULL)
		{
			matrix = ft_split(env[j], '=');
			if (malloc_p(matrix) == 1 && ft_strncmp(matrix[0], str, ft_strlen(str) + 1) != 0)
				matrix2[++i] = ft_strjoin(env[j], "\0");
			free_matrix(matrix);
		}
		matrix2[++i] = NULL;
		free_matrix(env);
		env = matrix2;
	}
	free_matrix(arg);
	free(str);
	return (1);
}
