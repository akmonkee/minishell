/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2025/01/15 13:17:49 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*redircmd(t_cmd *subcmd, char *file, int here_doc, int mode)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->here_doc = here_doc;
	cmd->mode = mode;
	if (mode == O_RDONLY)
		cmd->fd = 0;
	else if (mode == O_WRONLY|O_CREAT)
		cmd->fd = 1;
	return ((t_cmd *)cmd);
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int		tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			write(2, "Error\n missing file for redirection\n", 36);
		if (tok == '<')
			cmd = redircmd(cmd, q, 0, O_RDONLY);
		else if (tok == '-')
			cmd = redircmd(cmd, q, 1, O_WRONLY|O_CREAT|O_TRUNC);
		else if (tok == '>')
			cmd = redircmd(cmd, q, 0, O_WRONLY|O_CREAT|O_TRUNC);
		else if (tok == '+')
			cmd = redircmd(cmd, q, 0, O_WRONLY|O_CREAT|O_APPEND);
	}
	return (cmd);
}
