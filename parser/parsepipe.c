/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsepipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:19:10 by msisto            #+#    #+#             */
/*   Updated: 2024/12/19 14:56:39 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_cmd	*parsepipe(char **ps, char *es)
{
	t_cmd	*cmd;

	cmd = parseexec(ps, es);
	if(peek(ps, es, "|")){
		gettoken(ps, es, 0, 0);
		//cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return cmd;
}
