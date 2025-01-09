/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:09:31 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 17:09:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

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

static int	skip_char(int i, const char *s, char c)
{
	while (s[i] == c)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char	**matrix;
	int		i;
	int		j;
	int		k;

	if (s == NULL)
		return (NULL);
	matrix = malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (matrix == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		i = skip_char(i, s, c);
		k = i;
		while (s[i] && s[i] != c)
			i++;
		matrix[j] = ft_substr(s, k, i - k);
		i = skip_char(i, s, c);
		j++;
	}
	matrix[j] = NULL;
	return (matrix);
}
