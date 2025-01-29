/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:10:31 by msisto            #+#    #+#             */
/*   Updated: 2025/01/29 10:49:09 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*quote_extractor(char *q, char *eq)
{
	int		i;
	char	*ret;
	char	*start;

	i = 0;
	start = q;
	while (start != eq)
	{
		if (*start != 39)
			i++;
		start++;
	}
	start = q;
	ret = malloc(i + 1);
	i = 0;
	while (start != eq)
	{
		if (*start != 39)
		{
			ret[i] = *start;
			i++;
		}
		start++;
	}
	ret[i] = '\0';
	return (ret);
}
