/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:05 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:05 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//env mod

char	*ft_strjoinf12(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*ret;

	if (!s2)
		return (NULL);
	ret = malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	c = 0;
	while (s1[i])
		ret[c++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[c++] = s2[i++];
	ret[c] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

char	what_is_next(char *str, int flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && flag != 1)
			return (39);
		if (str[i] == '\"')
			return (34);
		if (str[i] == '$' && flag == 1)
			return (36);
		i++;
	}
	return (0);
}

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
	return (ret);
}

void	var_content_elab(char* var_content, char **env)
{
	int		k;
	int		flag[2];
	char	*ret;
	char	*b_quote;
	char	*tmp;

	k = -1;
	flag[0] = 0;
	flag[1] = 0;
	ret = NULL;
	if (!what_is_next(var_content, 0))
	{
		ret = ambient_value(var_content, env);
		free(ret);
		return ;
	}
	while (var_content[++k])
	{
		if (var_content[k] == flag[1])
		{
			flag[0] = 0;
			flag[1] = 0;
			k++;
			b_quote = var_ex(var_content + k, what_is_next(var_content + k, 0));
			if (b_quote)
				ret = ft_strjoinf12(ret, b_quote);
		}
		if ((var_content[k] == '\'' || var_content[k] == '\"') && flag[0] != 1)
		{
			flag[0] = 1;
			if (var_content[k] == '\'')
				flag[1] = 39;
			else
				flag[1] = 34;
			if (!ret)
				ret = var_ex(var_content, flag[1]);
			tmp = var_ex(var_content + k + 1, flag[1]);
			ret = ft_strjoinf12(ret, tmp);
			while (var_content[k] && var_content[k] != flag[1])
				k++;
		}
		if (var_content[k] == '\0')
			break ;
	}
	if (ret)
	{
		free(ret);
	}
}

char	*a_var_update(char *var, char *env_l, char **env)
{
	char	*var_name;
	char	*ret;
	char	*var_content;
	int		k;

	k = -1;
	var_name=var_ex(var, '=');
	while (var[++k] && var[k] != '=')
		;
	var_content = var_ex(var + k + 1, '\0');
	var_content_elab(var_content, env);
	k = -1;
	ret = malloc(ft_strlen_g(var) + 1);
	while (var[++k])
		ret[k] = var[k];
	ret[k] = '\0';
	free(env_l);
	free(var_name);
	free(var_content);
	return (ret);
}

void	**export_ccc(char *var, char **env)
{
	char	**tmp;
	char	*ex_var;
	char	*ex_env;
	int		i;

	i = 0;
	ex_var = var_ex(var, '=');
	while (env[i] != NULL)
	{
		ex_env = var_ex(env[i], '=');
		if (varcmp(ex_var, ex_env, ft_strlen_g(ex_var)) == 1)
		{
			env[i] = a_var_update(var, env[i], env);
			free(ex_env);
			free(ex_var);
			return ((void **)env);
		}
		free(ex_env);
		i++;
	}
	free(ex_var);
	i = mtx_len(env);
	tmp = (char **)ft_realloc(env, i + 1);
	tmp[i] = strdup(var);
	return ((void**)tmp);
}

void	**ft_realloc(char **mtx, int size)
{
	char	**ret;
	int		i;
	int		mtx_l;

	i = -1;
	mtx_l = mtx_len(mtx);
	ret = malloc((size + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (++i < size)
	{
		if (i < mtx_l)
			ret[i] = mtx[i];
		else
			ret[i] = NULL;
	}
	ret[i] = NULL;
	free(mtx);
	return ((void **)ret);
}

//main export function

void	**builtin_export(char *input, char **env)
{
	char	**var;
	char	**tmp;
	int		i;

	i = 1;
	var = ft_split(input, ' ', 0, 0);
	if (var[i] == NULL)
	{
		sort_env(env);
		mtxs_free(var);
		return (NULL);
	}
	tmp = env_cloner(env);
	while (var[i] != NULL)
	{
		if (arg_validation(var[i]))
			tmp = (char **)export_ccc(var[i], tmp);
		i++;
	}
	mtxs_free(var);
	return ((void **)tmp);
}
