/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:19:10 by msisto            #+#    #+#             */
/*   Updated: 2024/12/19 14:08:10 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct cmd	*parsepipe(char **ps, char *es)
{
	struct cmd	*cmd;

	//cmd = parseexec(ps, es, 0);
	if (peek(ps, es, "|"))
	{
		gettoken(ps, es, 0, 0);
		//cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}
