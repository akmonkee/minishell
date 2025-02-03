/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2025/01/31 11:47:40 by msisto           ###   ########.fr       */
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
	int		tok[2];
	char	*name;
	char	*q;
	char	*eq;

	while (peek(ps, es, "<>"))
	{
		tok[0] = gettoken(ps, es, 0, 0);
		tok[1] = gettoken(ps, es, &q, &eq);
		if (tok[1] != 'a' && tok[1] != 39)
		{
			write(2, "Error\n missing file for redirection\n", 36);
			exit (1);
		}
		if (check_singleq(q))
			name = quote_man(q, eq);
		else
			name = name_extractor(q, eq);
		if (tok[0] == '<')
			cmd = redircmd(cmd, name, 0, O_RDONLY);
		else if (tok[0] == '>')
			cmd = redircmd(cmd, name, 0, O_WRONLY|O_CREAT|O_TRUNC);
		else if (tok[0] == '+')
			cmd = redircmd(cmd, name, 0, O_WRONLY|O_CREAT|O_APPEND);
		else if (tok[0] == '-')
			cmd = redircmd(cmd, name, 1, O_WRONLY|O_CREAT|O_TRUNC);
	}
	return (cmd);
}
