/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_var_exp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 15:39:13 by msisto            #+#    #+#             */
/*   Updated: 2025/03/10 15:42:52 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*find_n_ret(char *name, char **env)
{
	int		k;
	int		j;
	char	*ex_env;
	char	*ret;

	k = -1;
	while (env[++k])
	{
		ex_env = var_ex(env[k], '=');
		if (varcmp(name, ex_env, ft_strlen_g(name)) == 1)
		{
			j = -1;
			while (env[k][++j] != '=');
			ret = var_ex(env[k] + j + 1, '\0');
			free(ex_env);
			return (ret);
		}
		free(ex_env);
	}
	return (NULL);
}

char	*ambient_value(char* str, char **env)
{
	int		i;
	char	*tmp;
	char	*res;
	char	*ret;

	i = -1;
	ret = NULL;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			if (!ret)
				ret = var_ex(str, '$');
			tmp = var_ex(str + i + 1, what_is_next(str + i, 1));
			res = find_n_ret(tmp, env);
			if (res)
				ret = ft_strjoinf12(ret, res);
			free(tmp);
		}
	}
	if (!ret && what_is_next(str, 1) != 36)
		return(var_ex(str, '\0'));
	return (ret);
}

char	*exp_not_in_q(char *str, char *ret, char **env)
{
	char	*b_quote;
	char	*tmp;

	b_quote = var_ex(str, what_is_next(str, 0));
	tmp = ambient_value(b_quote, env);
	free(b_quote);
	if (!ret)
	{
		ret = var_ex(tmp, '\0');
		free(tmp);
	}
	else if (tmp)
		ret = ft_strjoinf12(ret, tmp);
	return (ret);
}

char	*quote_elab(char *str, int flag, char *ret, char **env)
{
	char	*tmp;
	char	*b_quote;

	if (flag == '\"')
	{
		b_quote = var_ex(str + 1, flag);
		tmp = ambient_value(b_quote, env);
		free(b_quote);
	}
	if (!ret)
	{
		if (flag == '\"')
		{
			ret = var_ex(tmp, '\0');
			free(tmp);
		}
		else
			ret = var_ex(str + 1, flag);
	}
	else
	{
		if (flag == '\'')
			tmp = var_ex(str + 1, flag);
		if (tmp)
			ret = ft_strjoinf12(ret, tmp);
	}
	return (ret);
}

char	*var_content_elab(char* var_content, char **env)
{
	int		k;
	int		flag;
	char	*ret;

	k = -1;
	ret = NULL;
	if (!what_is_next(var_content, 0))
		return (ambient_value(var_content, env));
	while (var_content[++k])
	{
		if (var_content[k] && var_content[k] != 34 && var_content[k] != 39)
		{
			ret = exp_not_in_q(var_content + k, ret, env);
			while (var_content[++k] && var_content[k] != what_is_next(var_content + k, 0))
				if (var_content[k + 1] == 0)
					break ;
		}
		if ((var_content[k] == 34 || var_content[k] == 39))
		{
			flag = var_content[k];
			ret = quote_elab(var_content + k, flag, ret, env);
			while (var_content[++k] && var_content[k] != flag)
				;
		}
	}
	return (ret);
}
