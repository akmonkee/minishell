/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2025/04/21 16:22:39 by msisto           ###   ########.fr       */
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

static t_redircmd	*init_redir_node(t_cmd *cmd, char **ps, char *es, char *flag, int *tok)
{
	char		*q;
	char		*eq;
	t_redircmd	*node;

	node = rcmd_alloc();
	tok[0] = gettoken(ps, es, 0, 0);
	tok[1] = gettoken(ps, es, &q, &eq);
	if (mf_error(cmd, node, tok[1]) == 1)
		return (NULL);
	pr_ull(cmd, node, q, eq);
	if (tok[0] == '<')
		pr_ll(node, 0, O_RDONLY, 0);
	else if (tok[0] == '>')
		pr_ll(node, 0, O_WRONLY | O_CREAT | O_TRUNC, 1);
	else if (tok[0] == '+')
		pr_ll(node, 0, O_WRONLY | O_CREAT | O_APPEND, 1);
	else if (tok[0] == '-')
		pr_ll(node, 1, O_WRONLY | O_CREAT | O_APPEND, 1);
	node->cmd = NULL;
	return (node);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es, char *flag)
{
	int			tok[2];
	t_redircmd	*node;
	t_redircmd	*last;
	t_cmd		*head;

	head = cmd;
	last = NULL;
	while (peek(ps, es, flag))
	{
		node = init_redir_node(cmd, ps, es, flag, tok);
		if (!node)
			return (NULL);
		if (last)
			last->cmd = (t_cmd *)node;
		else
			head = (t_cmd *)node;
		last = node;
	}
	if (last)
		last->cmd = cmd;
	return (head);
}
