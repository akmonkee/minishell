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

int	builtin_unset(t_main *main, t_cmd *cur, int j, char *str)
{
	int		i;
	char	**arg;
	char	**matrix2;
	char	**matrix;

	i = -1;
	arg = take_args(main, cur, cur->cmd);
	if (malloc_p(arg) == 1 && ft_matrixlen(arg) > 1 && looking_for_env(main, str) != 0)
	{
		matrix2 = malloc((ft_matrixlen(main->env)) * sizeof(char *));
		while (malloc_p(arg) && main->env[++j] != NULL)
		{
			matrix = ft_split(main->env[j], '=');
			if (malloc_p(matrix) == 1 && ft_strncmp(matrix[0], str, ft_strlen(str) + 1) != 0)
				matrix2[++i] = ft_strjoin(main->env[j], "\0");
			free_matrix(matrix);
		}
		matrix2[++i] = NULL;
		free_matrix(main->env);
		main->env = matrix2;
	}
	free_matrix(arg);
	free (str);
	return (1);
}
