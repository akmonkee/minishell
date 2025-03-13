/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:23:15 by msisto            #+#    #+#             */
/*   Updated: 2025/03/13 10:23:31 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_scroll(char **s, char *es, int ret)
{
	char	*p;

	p = *s;
	while (p < es && !ft_strchr(WHITE_SPACE, *p) && !ft_strchr(SYMBOLS, *p))
	{
		if(parse_squote(p, es) == 1)
		{
			p++;
			while (p < es)
			{
				if (*p == 39)
					break ;
				p++;
			}
		}
		p++;
	}
	*s = p;
	return (ret);
}
