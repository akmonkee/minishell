/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:11:35 by efoschi           #+#    #+#             */
/*   Updated: 2024/12/02 14:57:35 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_pipe(char *s, char *es, t_cmd *cmd)
{
	char	*ps;
	char	*es;
	char	*qs;
	char	*qe;
	int		ret;

	ps = s;
	es = ps + ft_strlen(ps);
	ret = gettoken(&ps, es, 0, 0);
	if (ret == '|')
	{
		cmd->type = '|';
		return (1);
	}
	return (0);
}

int	parse_line(char *s, t_cmd *cmd)
{
	char	*es;
	int		ret;

	es = s + ft_strlen(s);
	ret = parse_pipe(s, es, cmd);
	if (ret)
		return (ret);
	return (0);
}

int	parse(char *s, t_cmd *cmd)
{
	return (parse_line(s, cmd));
}
