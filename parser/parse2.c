/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:23:15 by msisto            #+#    #+#             */
/*   Updated: 2025/03/24 16:30:11 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	s_scroll(char **s, char *es, int ret)
{
	char	*p;
	char	flag;

	p = *s;
	flag = '\0';
	while (p < es && !ft_strchr(WHITE_SPACE, *p) && !ft_strchr(SYMBOLS, *p))
	{
		if (*p == 39 || *p == 34)
			flag = *p;
		if(parse_squote(p, es, flag) == 1)
		{
			p++;
			while (p < es)
			{
				if (*p == flag)
					break ;
				p++;
			}
		}
		flag = '\0';
		p++;
	}
	*s = p;
	return (ret);
}
