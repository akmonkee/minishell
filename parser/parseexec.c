/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:53:56 by msisto            #+#    #+#             */
/*   Updated: 2025/04/03 17:11:29 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*execcmd(void)
{
	t_execcmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd *)cmd);
}

static int	s_error(t_cmd *cmd, int tok)
{
	if (tok != 'a' && tok != 39)
	{
		panic_fun("Error\n", "syntax\n", 1, 0);
		freecmd(cmd);
		free(cmd);
		return (1);
	}
	return (0);
}

static int	max_error(t_cmd *cmd, int argc)
{
	if (argc == MAXARGS)
	{
		panic_fun("Error\n", "too many args\n", 1, 0);
		freecmd(cmd);
		free(cmd);
		return (1);
	}
	if (!cmd)
		return (1);
	return (0);
}

t_cmd	*parseexec(char **ps, char *es, char *q, char *eq)
{
	int			tok;
	int			argc;
	t_execcmd	*cmd;
	t_cmd		*ret;

	ret = execcmd();
	cmd = (t_execcmd *) ret;
	argc = 0;
	ret = parseredirs(ret, ps, es, "<>");
	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (tok == 0)
			break ;
		if (s_error(ret, tok) == 1)
			return (NULL);
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (max_error(ret, argc) == 1)
			return (NULL);
		ret = parseredirs(ret, ps, es, "<>");
	}
	return (ret);
}
