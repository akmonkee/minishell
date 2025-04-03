/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_av_n_ll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:45 by msisto            #+#    #+#             */
/*   Updated: 2025/04/03 10:15:13 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*av_less_lines(char *str, int i, char **env)
{
	char	*tmp;
	char	*res;

	res = NULL;
	if (str[i + 1] == '?')
	{
		res = ft_itoa(g_exit_code);
		if (str[i + 2] != '$')
		{
			tmp = var_ex(str + i + 2, what_is_next(str + i, 2));
			res = ft_strjoinf12(res, tmp);
		}
	}
	else if (str[i + 1] != '\0')
	{
		tmp = var_ex(str + i + 1, what_is_next(str + i, 1));
		res = find_n_ret(tmp, env);
		free(tmp);
	}
	return (res);
}

char	*ambient_value(char *str, char **env)
{
	int		i;
	char	*res;
	char	*ret;

	i = -1;
	ret = NULL;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '\0')
			{
				ret = var_ex(str, '\0');
				break ;
			}
			if (!ret)
				ret = var_ex(str, '$');
			res = av_less_lines(str, i, env);
			if (res)
				ret = ft_strjoinf12(ret, res);
		}
	}
	if (!ret && what_is_next(str, 1) != 36)
		return (var_ex(str, '\0'));
	return (ret);
}
