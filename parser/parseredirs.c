/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2025/04/03 16:06:17 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pr_ll(t_redircmd *rcmd, int here_doc, int mode, int fd)
{
	rcmd->here_doc = here_doc;
	rcmd->mode = mode;
	rcmd->fd = fd;
}

static int	mf_error(t_cmd *cmd, t_redircmd *rcmd, int tok)
{
	if (tok != 'a' && tok != 39)
	{
		panic_fun("Error\n", "missing file for redirection\n", 2, 0);
		freecmd(cmd);
		free(cmd);
		free(rcmd);
		return (1);
	}
	return (0);
}

static void	pr_ull(t_cmd *cmd, t_redircmd *rcmd, char *q, char *eq)
{
	rcmd->type = REDIR;
	rcmd->cmd = cmd;
	if (rcmd->file)
		free(rcmd->file);
	rcmd->file = name_extractor(q, eq);
}

static t_redircmd	*rcmd_alloc(void)
{
	t_redircmd	*rcmd;

	rcmd = malloc(sizeof(*rcmd));
	ft_memset(rcmd, 0, sizeof(*rcmd));
	return (rcmd);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, char *flag)
{
	int			tok[2];
	char		*q;
	char		*eq;
	t_redircmd	*rcmd;

	rcmd = rcmd_alloc();
	while (peek(ps, es, flag))
	{
		tok[0] = gettoken(ps, es, 0, 0);
		tok[1] = gettoken(ps, es, &q, &eq);
		if (mf_error(cmd, rcmd, tok[1]) == 1)
			return (NULL);
		pr_ull(cmd, rcmd, q, eq);
		if (tok[0] == '<')
			pr_ll(rcmd, 0, O_RDONLY, 0);
		else if (tok[0] == '>')
			pr_ll(rcmd, 0, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok[0] == '+')
			pr_ll(rcmd, 0, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok[0] == '-')
			pr_ll(rcmd, 1, O_WRONLY | O_CREAT | O_APPEND, 1);
	}
	if (rcmd->type == REDIR)
		return ((t_cmd *)rcmd);
	return (free(rcmd), cmd);
}
