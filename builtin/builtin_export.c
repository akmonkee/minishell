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

char	*a_var_update(char *var, char *env)
{
	int		k;
	char	*ret;

	k = 0;
	ret = malloc(ft_strlen_g(var) + 1);
	while (var[k])
	{
		ret[k] = var[k];
		k++;
	}
	ret[k] = '\0';
	free(env);
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
			env[i] = a_var_update(var, env[i]);
			free(ex_env);
			free(ex_var);
			return ((void **)env);
		}
		free(ex_env);
		i++;
	}
	free(ex_var);
	tmp = (char **)ft_realloc(env, mtx_len(env) + 1);
	mtxs_free(env);
	return ((void**)tmp);
}

void	**ft_realloc(char **mtx, int size)
{
	char	**ret;
	int		i;
	int		mtx_l;

	i = 0;
	mtx_l = mtx_len(mtx);
	ret = malloc((size + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (i < size)
	{
		if (i < mtx_l)
			ret[i] = strdup(mtx[i]);
		else
		{
			ret[i] = malloc(1);
			ret[i][0] = '\0';
		}
		i++;
	}
	ret[i] = NULL;
	return ((void **)ret);
}

int	builtin_export(char *input, char **env)
{
	char	**var;
	int		i;

	i = 1;
	var = ft_split(input, ' ', 0, 0);
	if (var[i] == NULL)
	{
		builtin_env(env, 1);
		mtxs_free(var);
		return (0);
	}
	printf("pre realloc %p\n", env);
	while (var[i] != NULL)
	{
		if (ft_strnstr(var[i], "=", ft_strlen_g(var[i])) != 0)
			env = (char **)export_ccc(var[i], env);
		i++;
	}
	printf("post realloc %p\n", env);
	mtxs_free(var);
	return (0);
}
