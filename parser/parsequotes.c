/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsequotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 12:19:49 by msisto            #+#    #+#             */
/*   Updated: 2025/05/06 10:25:25 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	single_quote(char *s, char *es)
{
	while (s < es)
	{
		if (*s == 39)
		{
			return (39);
		}
		s++;
	}
	return (0);
}

int	mf_error(t_cmd *cmd, t_redircmd *rcmd, int tok)
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
