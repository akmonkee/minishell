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

char	*a_var_update(char *var, char *env_l, char **env)
{
	char	*tmp;
	char	*var_name;
	char	*ret;
	char	*var_content;
	int		k;

	k = -1;
	var_name=var_ex(var, '=');
	while (var[++k] && var[k] != '=')
		;
	var_content = var_ex(var + k + 1, '\0');
	tmp = var_content_elab(var_content, env);
	ret = var_ex(var_name, '\0');
	ret = ft_strjoinf1(ret, "=");
	ret = ft_strjoinf12(ret, tmp);
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
	tmp[i] = NULL;
	tmp[i] = a_var_update(var, tmp[i], tmp);
	return ((void**)tmp);
}

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
