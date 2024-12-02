/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:17:55 by msisto            #+#    #+#             */
/*   Updated: 2024/12/02 14:54:56 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gettoken(char **ps, char *es, char **q, char **eq)
{
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(s, WHITE_SPACE))
		s++;
	if (q)
		*q = s;
	ret = *s;
	/*
	parse options here
	*/
	if (eq)
		*eq = s;
	while (s < es && ft_strchr(s, WHITE_SPACE))
		s++;
	*ps = s;
	return (ret);
}
