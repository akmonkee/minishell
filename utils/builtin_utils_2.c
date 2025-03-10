/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:12:15 by efoschi           #+#    #+#             */
/*   Updated: 2025/03/10 15:12:15 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

static char	**allocate_matrix(char const *s, char c)
{
	char	**matrix;
	int		word_count;
	int		j;

	word_count = ft_count_words(s, c);
	matrix = malloc(sizeof(char *) * (word_count + 1));
	if (!matrix)
		return (NULL);
	j = 0;
	while (j <= word_count)
	{
		matrix[j] = NULL;
		j++;
	}
	return (matrix);
}

static int	fill_matrix_helper(char const *s, char **matrix, int *j, int k, int i)
{
	matrix[*j] = ft_substr(s, k, i - k);
	if (!matrix[*j])
	{
		while (*j > 0)
			free(matrix[--(*j)]);
		free(matrix);
		return (0);
	}
	(*j)++;
	return (1);
}

static char	**fill_matrix(char const *s, char c, char **matrix)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (s[i] && j < ft_count_words(s, c))
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			k = i;
			while (s[i] && s[i] != c)
				i++;
			if (!fill_matrix_helper(s, matrix, &j, k, i))
				return (NULL);
		}
	}
	matrix[j] = NULL;
	return (matrix);
}

char **ft_split_bt(char const *s, char c)
{
	char **matrix;

	if (!s)
		return (NULL);
	matrix = allocate_matrix(s, c);
	if (!matrix)
		return (NULL);
	return (fill_matrix(s, c, matrix));
}
