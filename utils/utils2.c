/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:06:06 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 17:06:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_space(int i, char *str)
{
	if (str == NULL)
		return (i);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			break ;
	}
	return (i);
}

int	go_next(int i, char *str)
{
	i = skip_space(i, str);
	while (str[i] && str[i] != ' ' && str[i] != '\0')
		i++;
	i = skip_space(i, str);
	return (i);
}

char	**copy_matrix(char **matrix)
{
	int		i;
	char	**new_matrix;

	i = 0;
	new_matrix = malloc(sizeof(char *) * (ft_matrixlen(matrix) + 1));
	while (matrix[i])
	{
		new_matrix[i] = ft_strjoin(matrix[i], "\0");
		i++;
	}
	new_matrix[i] = NULL;
	return (new_matrix);
}

char	*no_space(char *str)
{
	int	i;
	int	j;

	if (str == NULL)
		return (NULL);
	i = skip_space(0, str);
	j = i;
	while (str[i] != ' ' && str[i] != '\0')
		i++;
	return (ft_substr(str, j, i - j));
}
