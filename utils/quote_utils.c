/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:10:31 by msisto            #+#    #+#             */
/*   Updated: 2025/01/31 11:48:31 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_singleq(char *q)
{
	int	i;

	i = 0;
	while (q[i] != '\0' && q[i] != ' ')
	{
		if (q[i] == 39)
			return (1);
		i++;
	}
	return (0);
}

char	*quote_man(char *q, char *eq)
{
	char	*ret;
	char	*start;
	int		i;

	start = q;
	i = 0;
	while (start < eq)
	{
		if (*start != 39)
			i++;
		start++;
	}
	start = q;
	ret = malloc(i + 1);
	i = 0;
	while (start < eq)
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
