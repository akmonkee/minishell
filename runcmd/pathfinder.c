/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 11:17:05 by msisto            #+#    #+#             */
/*   Updated: 2024/12/20 13:21:57 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*path_ex(char *string, int ex_len, int start)
{
	char	*output;
	int		i;

	i = 0;
	output = malloc(ex_len + 1);
	if (!output)
		return (NULL);
	while (i < ex_len && string[start] != '\0')
	{
		output[i] = string[start];
		start++;
		i++;
	}
	output[ex_len] = '\0';
	return (output);
}

int	path_count(char *string, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (string[i])
	{
		if (string[i] != c && (string[i + 1] == c || string[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

char	**ft_split(char *string, char c, int index, int start)
{
	char	**output;
	int		i;
	int		strlen;

	i = 0;
	strlen = 0;
	output = malloc((path_count(string, c) + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	while (string[start + i] != '\0')
	{
		if (string[start + i] == c)
		{
			output[index] = path_ex(string, strlen, start);
			index++;
			strlen = 0;
			start = start + i + 1;
			i = 0;
		}
		strlen++;
		i++;
	}
	output[index] = path_ex(string, strlen, start);
	output[index + 1] = NULL;
	return (output);
}

char	*ft_strnstr(const char *s, const char *to_find, size_t len)
{
	size_t	j;

	if (!*to_find)
		return ((char *)s);
	if (!len || !*s)
		return (NULL);
	while (*s && len > 0)
	{
		if (*s == *to_find)
		{
			j = 0;
			while (j < len && to_find[j] && s[j] == to_find[j])
				j++;
			if (to_find[j] == '\0')
				return ((char *)s);
		}
		s++;
		len--;
	}
	return (0);
}

char	**path_finder(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PATH", 4))
		i++;
	paths = ft_split(envp[i], ':', 0, 5);
	return (paths);
}
