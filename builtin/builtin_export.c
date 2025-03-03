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

char	*a_var_update(char *var, char *env)
{
	char	*ret;
	int		k;

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

	i = 0;
	mtx_l = mtx_len(mtx);
	ret = malloc((size + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (i < size)
	{
		if (i < mtx_l)
			ret[i] = mtx[i];
		else
			ret[i] = NULL;
		i++;
	}
	ret[i] = NULL;
	free(mtx);
	return ((void **)ret);
}

//sorting and printing env

void	p_export(char **env_cp)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (env_cp[++i])
	{
		len = -1;
		while (env_cp[i][++len] && env_cp[i][len] != '=')
			;
		j = -1;
		printf("declare -x ");
		while (++j < len)
			printf("%c", env_cp[i][j]);
		if (len < ft_strlen_g(env_cp[i]) && ft_strchr(env_cp[i], '='))
			printf("=\"%s\"", env_cp[i] + len + 1);
		printf("\n");
	}
}

void	sort_env(char **env)
{
	int		i;
	int		k;
	int		size;
	char	*tmp;
	char	**env_cp;

	size = mtx_len(env);
	env_cp = env_cloner(env);
	i = -1;
	while (++i < size - 1)
	{
		k = -1;
		while (++k < size - i - 1)
		{
			if (strcmp(env_cp[k], env_cp[k + 1]) > 0)
			{
				tmp = env_cp[k];
				env_cp[k] = env_cp[k + 1];
				env_cp[k + 1] = tmp;
			}
		}
	}
	p_export(env_cp);
	mtxs_free(env_cp);
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
		if ((var[i][0] >= 33 && var[i][0] <= 64) || (var[i][0] >= 91 && var[i][0] <= 96) || (var[i][0] >= 123 && var[i][0] <= 126))
		{
			perror("not a valid identifier\n");
			g_exit_code = 1;
			break ;
		}
		if (ft_strnstr(var[i], "=", ft_strlen_g(var[i])) != 0)
			tmp = (char **)export_ccc(var[i], tmp);
		i++;
	}
	mtxs_free(var);
	return ((void **)tmp);
}
