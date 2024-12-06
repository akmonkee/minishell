/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:19:10 by msisto            #+#    #+#             */
/*   Updated: 2024/12/06 12:19:59 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

struct cmd	*parsepipe(char **ps, char *es)
{
	struct cmd	*cmd;

	//cmd = parseexec(ps, es);
	if(peek(ps, es, "|")){
		gettoken(ps, es, 0, 0);
		//cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return cmd;
}
