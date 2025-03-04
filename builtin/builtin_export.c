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

void	var_content_elab(char* var_content)
{
	int		k;
	int		flag[2];
	char	*ret;
	char	*tmp;

	k = -1;
	flag[0] = 0;
	flag[1] = 0;
	ret = NULL;
	while (var_content[++k])
	{
		if (var_content[k] == flag[1])
		{
			flag[0] = 0;
			flag[1] = 0;
			k++;
		}
		if (var_content[k] == '\'' && flag[0] != 1)
		{
			flag[0] = 1;
			flag[1] = 39;
			if (!ret)
				ret = var_ex(var_content, flag[1]);
			tmp = var_ex(var_content + k + 1, flag[1]);
			ret = ft_strjoinf12(ret, tmp);
			while (var_content[k] && var_content[k] != flag[1])
				k++;
		}
		if (var_content[k] == '\"' && flag[0] != 1)
		{
			flag[0] = 1;
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
		printf("%s\n", ret);
		free(ret);
	}
}

char	*a_var_update(char *var, char *env)
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
	var_content_elab(var_content);
	k = -1;
	ret = malloc(ft_strlen_g(var) + 1);
	while (var[++k])
		ret[k] = var[k];
	ret[k] = '\0';
	free(env);
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
		if (arg_validation(var[i]))
			tmp = (char **)export_ccc(var[i], tmp);
		i++;
	}
	mtxs_free(var);
	return ((void **)tmp);
}
