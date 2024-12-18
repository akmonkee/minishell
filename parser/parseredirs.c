/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseredirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:58:05 by msisto            #+#    #+#             */
/*   Updated: 2024/12/18 12:26:16 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			/*redir with O_RDONLY*/
		else if (tok == '>')
			/*redir with O_WRONLY and O_CREATE*/
		else if (tok == '+')
			/*redir with O_WRONLY and O_CREATE*/
	}
	return (cmd);
}
