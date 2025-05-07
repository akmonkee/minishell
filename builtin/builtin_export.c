/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:04:54 by msisto            #+#    #+#             */
/*   Updated: 2025/05/07 10:04:54 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	what_is_next(char *str, int flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && flag != 2)
			return (39);
		if (str[i] == '\"')
			return (34);
		if (str[i] == '$' && flag != 0)
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
	char	*ret;
	char	*var_content;
	int		k;

	k = -1;
	while (var[++k])
	{
		if (var[k] == '=')
			break ;
	}
	if (var[k] == '\0')
		return (var_ex(var, '\0'));
	k = -1;
	ret = var_ex(var, '=');
	while (var[++k] && var[k] != '=')
		;
	var_content = var_ex(var + k + 1, '\0');
	tmp = var_content_elab(var_content, env);
	ret = ft_strjoinf1(ret, "=");
	ret = ft_strjoinf12(ret, tmp);
	free(env_l);
	free(var_content);
	return (ret);
}

void	**export_ccc(char *var, char **env)
{
	char	**tmp;
	char	*ex_var;
	char	*ex_env;
	int		i;

	i = -1;
	ex_var = var_ex(var, '=');
	while (env[++i] != NULL)
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
	}
	free(ex_var);
	i = mtx_len(env);
	tmp = (char **)ft_realloc(env, i + 1);
	tmp[i] = NULL;
	tmp[i] = a_var_update(var, tmp[i], tmp);
	return ((void **) tmp);
}

void	**builtin_export(char **input, char **env)
{
	char	**tmp;
	char	*ret;
	int		i;

	i = 1;
	if (!env)
		return (NULL);
	if (input[i] == NULL)
		return (sort_env(env), NULL);
	tmp = env_cloner(env);
	while (input[i] != NULL)
	{
		if (input[i][0] == '\"' || input[i][0] == '\'')
		{
			ret = var_content_elab(input[i], tmp);
			arg_validation(ret);
			tmp = (char **)be_ll(ret, tmp);
		}
		else if (arg_validation(input[i]))
			tmp = (char **)export_ccc(input[i], tmp);
		i++;
	}
	return ((void **)tmp);
}
