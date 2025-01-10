/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:57:28 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 11:57:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	word_count(int *word, char *str, int *i, char c)
{
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	(*word)++;
}

char	*substr_extract(char *str, int *i, char c)
{
	int	j;

	j = *i;
	(*i)++;
	while (str[*i] != '\0' && str[*i] != c)
		(*i)++;
	return (ft_substr(str, j, *i - j));
}

char	*substr_extract2(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[*i] != '\0' && str[*i] != ' ')
		(*i)++;
	return (ft_substr(str, j, *i - j));
}

void	which_utils(char *str, int *i, int *word, char **matrix)
{
	if (str[*i] == '\'')
		matrix[*word] = substr_extract(str, i, '\'');
	else if (str[*i] == '\"')
		matrix[*word] = substr_extract(str, i, '\"');
	else if (str[*i] == ' ')
		matrix[*word] = substr_extract2(str, i);
	else
		(*i)++;
	if (str[*i] == '\'' || str[*i] == '\"')
		(*i)++;
	*i = skip_space(*i, str);
	(*word)++;
}
