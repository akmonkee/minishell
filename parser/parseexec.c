/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:53:56 by msisto            #+#    #+#             */
/*   Updated: 2024/12/16 11:32:14 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct cmd	*execcmd()
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((struct cmd*)cmd);
}

struct cmd	*parseexec(char **ps, char *es, int argc)
{
	char	*q;
	char	*eq;
	int		tok;
	t_execcmd	*cmd;
	struct cmd	*ret;

	if (peek(ps, es, "("))
		/*parseblock*/
	ret = execcmd();
	cmd = (t_execcmd*)ret;
	argc = 0;
	while (!peek(ps, es, "|)&;"))
	{
		if ((tok = gettoken(ps, es, &q, &eq)) == 0)
			break ;
		if (tok != 'a')
			/*print error "syntax"*/
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		//if (argc >= MAXARGS)
			/*print error "too many args"*/
		/*find out why parseredir is here*/
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return (ret);
}