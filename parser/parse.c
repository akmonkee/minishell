/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:17:55 by msisto            #+#    #+#             */
/*   Updated: 2025/04/17 15:43:25 by msisto           ###   ########.fr       */
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

int	redir_check(char **s, char redir, int curr_ret)
{
	int		ret;
	char	*p;

	p = *s;
	p++;
	ret = curr_ret;
	if (*p == redir)
	{
		if (redir == '<')
		{
			ret = '-';
			p++;
		}
		if (redir == '>')
		{
			ret = '+';
			p++;
		}
	}
	*s = p;
	return (ret);
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
		s++;
	else if (*s == '<')
		ret = redir_check(&s, '<', ret);
	else if (*s == '>')
		ret = redir_check(&s, '>', ret);
	else
		ret = s_scroll(&s, es, 'a');
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
	return (cmd);
}

t_cmd	*parsecmd(char *s)
{
	char	*es;
	t_cmd	*cmd;

	es = s + ft_strlen(s);
	cmd = parseline(&s, es);
	if (!cmd)
		return (NULL);
	peek(&s, es, "");
	if (s != es)
	{
		panic_fun("Error\n", "end of command not reached\n", 1, 0);
		freecmd(cmd);
		free(cmd);
		return (NULL);
	}
	nulterminate(cmd);
	return (cmd);
}
