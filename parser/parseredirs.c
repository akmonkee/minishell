/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2024/12/19 14:48:59 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*redircmd(t_cmd *subcmd, char *file, char *efile, int mode)
{
	t_redircmd	*cmd;

	cmd = malloc(sizeof(*cmd));
	ft_memset(cmd, 0, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	if (mode > 0)
		cmd->fd = 0;
	else
		cmd->fd = 1;
	return (t_cmd *)cmd;
}

t_cmd	*parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int	tok;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			/*print error "missing file for redirection"*/
		if (tok == '<')
			cmd = redircmd(cmd, q, eq, O_RDONLY);
		else if (tok == '>')
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT);
		else if (tok == '+')
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT);
	}
	return (cmd);
}
