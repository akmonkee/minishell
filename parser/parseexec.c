/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:53:56 by msisto            #+#    #+#             */
/*   Updated: 2025/03/17 13:51:34 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*execcmd()
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

t_cmd	*parseexec(char **ps, char *es)
{
	char	*q;
	char	*eq;
	int		tok;
	int		argc;
	t_execcmd	*cmd;
	t_cmd	*ret;

	ret = execcmd();
	cmd = (t_execcmd*)ret;
	argc = 0;
	ret = parseredirs(ret, ps, es);
	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		else if (tok != 'a' && tok != 39)
		{
			write(2, "Error\nsyntax\n", 13);
			exit (1);
		}
		if (check_singleq(q))
			cmd->argv[argc] = quote_man(q, eq);
		else
			cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
		{
			write(2, "Error\ntoo many args\n", 20);
			exit (1);
		}
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}
