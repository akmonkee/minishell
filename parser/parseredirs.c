/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2025/04/17 15:55:14 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	pr_ll(t_redircmd *rcmd, int here_doc, int mode, int fd)
{
	rcmd->here_doc = here_doc;
	rcmd->mode = mode;
	rcmd->fd = fd;
	rcmd->here_doc_name = NULL;
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
	rcmd->here_doc_name = NULL;
}

static t_redircmd	*rcmd_alloc(void)
{
	t_redircmd	*rcmd;

	rcmd = malloc(sizeof(*rcmd));
	ft_memset(rcmd, 0, sizeof(*rcmd));
	return (rcmd);
}

/*t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, char *flag)
{
	int			tok[2];
	char		*q;
	char		*eq;
	t_redircmd	*rcmd;

	while (peek(ps, es, flag))
	{
		rcmd = rcmd_alloc();
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
		cmd = (t_cmd *)rcmd;
	}
	return (cmd);
}*/

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, char *flag)
{
	int			tok[2];
	char		*q;
	char		*eq;
	t_redircmd	*new_rcmd;
	t_redircmd	*last_rcmd;
	t_cmd		*head;

	head = cmd;
	last_rcmd = NULL;
	while (peek(ps, es, flag))
	{
		new_rcmd = rcmd_alloc();
		tok[0] = gettoken(ps, es, 0, 0);
		tok[1] = gettoken(ps, es, &q, &eq);
		if (mf_error(cmd, new_rcmd, tok[1]) == 1)
			return (NULL);
		pr_ull(cmd, new_rcmd, q, eq);
		if (tok[0] == '<')
			pr_ll(new_rcmd, 0, O_RDONLY, 0);
		else if (tok[0] == '>')
			pr_ll(new_rcmd, 0, O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (tok[0] == '+')
			pr_ll(new_rcmd, 0, O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (tok[0] == '-')
			pr_ll(new_rcmd, 1, O_WRONLY | O_CREAT | O_APPEND, 1);
		new_rcmd->cmd = NULL;
		if (last_rcmd)
			last_rcmd->cmd = (t_cmd *)new_rcmd;
		else
			head = (t_cmd *)new_rcmd;
		last_rcmd = new_rcmd;
	}
	if (last_rcmd)
		last_rcmd->cmd = cmd;
	return (head);
}
