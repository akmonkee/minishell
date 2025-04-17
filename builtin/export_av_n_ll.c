/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_av_n_ll.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 13:30:45 by msisto            #+#    #+#             */
/*   Updated: 2025/04/17 11:47:20 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*av_ll_ll_ll(char *res, char *str, int i)
{
	char	*tmp;

	if (str[i] != '\0' && str[i] == str[i + 1])
		res = ft_strjoinf1(res, "\'\'");
	else if (!what_is_next(str + i + 1, 2))
	{
		tmp = var_ex(str + i, '\0');
		res = ft_strjoinf12(res, tmp);
	}
	else
	{
		tmp = var_ex(str + i, what_is_next(str + i + 1, 1));
		res = ft_strjoinf12(res, tmp);
	}
	return (res);
}

static char	*av_ll_ll(char *res, char *str, int i, char **env)
{
	char	*tmp;
	int		flag;

	tmp = var_ex(str + i + 1, what_is_next(str + i + 1, 1));
	flag = what_is_next(str + i + 1, 1);
	while (str[i] && str[i] != flag)
		i++;
	res = find_n_ret(tmp, env);
	free(tmp);
	if (str[i] == '\0')
		return (res);
	flag = what_is_next(str + i + 1, 2);
	if (flag == '$')
	{
		tmp = var_ex(str + i, '$');
		res = ft_strjoinf12(res, tmp);
	}
	else if (str[i] != '\0')
		res = av_ll_ll_ll(res, str, i);
	return (res);
}

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
		res = av_ll_ll(res, str, i, env);
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
