/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:17:55 by msisto            #+#    #+#             */
/*   Updated: 2024/12/05 15:10:15 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	peek(char **ps, char *es, char *toks)
{
	char	*s;

	s = *ps;
	while (s < es && ft_strchr(WHITE_SPACE, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(toks, *s));
}

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(WHITE_SPACE, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		return (0);
	else if (*s == '|')
	{
		return (124);
	}
	/*
	parse options here
	*/
	else
	{
		ret = 'a';
		while (s < es && !ft_strchr(WHITE_SPACE, *s) && !ft_strchr(SYMBOLS, *s))
			s++;
	}
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(WHITE_SPACE, *s))
		s++;
	*ps = s;
	return (ret);
}
