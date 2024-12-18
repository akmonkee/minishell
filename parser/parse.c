/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:17:55 by msisto            #+#    #+#             */
/*   Updated: 2024/12/18 12:28:34 by msisto           ###   ########.fr       */
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

t_cmd	*parseline(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parsepipe(ps, es);
}

t_cmd	*parsecmd(char *s)
{
	char		*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	peek(&s, es, "");
	if(s != es){
		write(2, "Error\nend of command not reached\n", 33);
		return (NULL);
	}
	//nulterminate(cmd);
	return (cmd);
}
