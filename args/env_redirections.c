/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:38:03 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 11:38:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fd_redir(char **matrix, int i, int j)
{
	if (j == 1)
		dup2(file_p(matrix[i + 1], 3), 1);
	else if (j == 2)
		dup2(file_p(matrix[i + 1], 4), 1);
	else if (j == 3)
		dup2(file_p(matrix[i + 1], 1), 0);
	else if (j == 4)
		//here_doc(matrix[i+1]);
	free(matrix[i]);
	free(matrix[i + 1]);
	matrix[i] = malloc(2);
	matrix[i][0] = ' ';
	matrix[i][1] = '\0';
	matrix[i + 1] = malloc(2);
	matrix[i + 1][0] = ' ';
	matrix[i + 1][1] = '\0';
}

static char	**no_space_matrix(char **matrix, int i, int j, int k)
{
	char	**new_matrix;

	new_matrix = malloc((i + 1) * sizeof(char *));
	malloc_p(new_matrix);
	while (matrix[j])
	{
		if (ft_strncmp(matrix[j], " ", 2))
			new_matrix[k] = ft_strjoin(matrix[j], "\0");
		k++;
	}
	new_matrix[k] = NULL;
	free_matrix(matrix);
	return (new_matrix);
}

char	**env_redir(char **matrix)
{
	int		i;

	i = 0;
	while (matrix[i])
	{
		if (!ft_strncmp(matrix[i], ">", 2) && matrix[i +1])
			fd_redir(matrix, i, 1);
		else if (!ft_strncmp(matrix[i], ">>", 3) && matrix[i + 1])
			fd_redir(matrix, i, 2);
		else if (!ft_strncmp(matrix[i], "<", 2) && matrix[i + 1])
			fd_redir(matrix, i, 3);
		else if (!ft_strncmp(matrix[i], "<<", 3) && matrix[i + 1])
			fd_redir(matrix, i, 4);
		i++;
	}
	return (no_space_matrix(matrix, i, 0, 0));
}
