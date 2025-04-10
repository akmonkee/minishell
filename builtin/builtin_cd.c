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

static void	**ambient_cd(char *input, char *curr_pwd, char **env)
{
	char	*path;

	path = var_content_elab(input, env);
	if (path[0] == '\0')
	{
		free(path);
		path = var_ex("/", '\0');
	}
	if (chdir(path) == -1)
	{
		panic_fun("cd :", path, 1, 0);
		free(path);
		free(curr_pwd);
		return (NULL);
	}
	return (env_mod(path, curr_pwd, env));
}

static void	**minus_cd(char *curr_pwd, char **env)
{
	char	*path;

	path = ambient_value("$OLDPWD", env);
	if (path[0] == '\0')
	{
		panic_fun("bash: cd: OLDPWD not set\n", NULL, 1, 0);
		free(path);
		free(curr_pwd);
		return (NULL);
	}
	chdir(path);
	return (env_mod(path, curr_pwd, env));
}

static void	**no_input_or_root(char *input, char *curr_pwd, char **env)
{
	char	*path;

	if (!input)
		path = ambient_value("$HOME", env);
	else if (fullcmp(input, "/") == 0)
		path = var_ex("/", '\0');
	chdir(path);
	return (env_mod(path, curr_pwd, env));
}

void	**builtin_cd(char *input, char **env)
{
	char	*curr_pwd;
	char	*path;

	if (!env)
		return (NULL);
	curr_pwd = true_pwd_ex();
	if (!input || fullcmp(input, "/") == 0)
		return (no_input_or_root(input, curr_pwd, env));
	else if (fullcmp(input, "-") == 0)
		return (minus_cd(curr_pwd, env));
	else if (what_is_next(input, 1) == '$')
		return (ambient_cd(input, curr_pwd, env));
	path = path_builder(input, curr_pwd);
	path = ft_strjoinf2("/", path);
	if (chdir(path) == -1)
	{
		panic_fun("cd :", input, 1, 0);
		free(path);
		return (free(curr_pwd), NULL);
	}
	g_exit_code = 0;
	return (env_mod(path, curr_pwd, env));
}
