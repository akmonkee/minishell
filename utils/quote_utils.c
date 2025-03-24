/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:10:31 by msisto            #+#    #+#             */
/*   Updated: 2025/03/24 16:30:27 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_squote(char *s, char *es, char flag)
{
	char	*st;

	st = s;
	if (flag == '\0')
		return (0);
	if (*st == flag)
	{
		st++;
		while (st < es)
		{
			if (*st == flag)
				return (1);
			st++;
		}
	}
	return (0);
}
