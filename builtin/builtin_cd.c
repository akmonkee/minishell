/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:55 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:55 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*strjoin_path(char *path, int flag)
{
	int		i;
	int		len;
	char	*ret;
	char	**path_s;

	i = 0;
	path_s = ft_split_bt(path, '/');
	len = mtx_len(path_s);
	if (flag == 1)
	{
		free(path);
		len--;
	}
	ret = var_ex(path_s[i], '\0');
	while (++i < len)
	{
		ret = ft_strjoinf1(ret, "/");
		ret = ft_strjoinf1(ret, path_s[i]);
	}
	mtxs_free(path_s);
	return (ret);
}

char	*path_builder(char *input, char *curr_pwd)
{
	int		i;
	char	*path;
	char	**split;

	if (ft_strlen_g(curr_pwd) != 1)
		path = strjoin_path(curr_pwd, 0);
	else
		path = var_ex(curr_pwd, '\0');
	split = ft_split_bt(input, '/');
	i = -1;
	while (split[++i] != NULL)
	{
		if (varcmp(split[i], "..", ft_strlen_g(split[i])) == 1)
			path = strjoin_path(path, 1);
		else
		{
			path = ft_strjoinf1(path, "/");
			path = ft_strjoinf1(path, split[i]);
		}
	}
	mtxs_free(split);
	return (path);
}

void	**pwd_mod(char *str, char **env)
{
	int		i;
	char	*var_name;
	char	*ex_env;
	char	**ret;

	i = -1;
	var_name = var_ex(str, '=');
	while (env[++i] != NULL)
	{
		ex_env =  var_ex(env[i], '=');
		if (varcmp(var_name, ex_env, ft_strlen_g(var_name)) == 1)
		{
			free(ex_env);
			free(var_name);
			free(env[i]);
			env[i] = var_ex(str, '\0');
			return ((void **)env);
		}
		free(ex_env);
	}
	free(var_name);
	i = mtx_len(env);
	ret = (char **)ft_realloc(env, i + 1);
	ret[i] = var_ex(str, '\0');
	return ((void**)ret);
}

void	**env_mod(char *path, char *curr_pwd, char **env)
{
	char *path_c;
	char *old_pwd;
	char **ret_env;

	path_c = ft_strjoinf2("PWD=", path);
	old_pwd = ft_strjoinf2("OLD_PWD=", curr_pwd);
	ret_env = env_cloner(env);
	ret_env = (char **)pwd_mod(path_c, ret_env);
	ret_env = (char **)pwd_mod(old_pwd, ret_env);
	free(path_c);
	free(old_pwd);
	return ((void **)ret_env);
}

void	**builtin_cd(char *input, char **env)
{
	char	**ret_env;
	char	*curr_pwd;
	char	*path;
	int		i;

	i = 0;
	curr_pwd = true_pwd_ex();
	if (!input || fullcmp(input, "/") == 0)
	{
		path = var_ex("/", '\0');
		chdir(path);
		ret_env = (char **)env_mod(path, curr_pwd, env);
		return ((void **) ret_env);
	}
	path = path_builder(input, curr_pwd);
	path = ft_strjoinf2("/", path);
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		free(path);
		free(curr_pwd);
		return (NULL);
	}
	ret_env = (char **)env_mod(path, curr_pwd, env);
	return ((void **) ret_env);
}
