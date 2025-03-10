/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:59:28 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:59:28 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char **remove_env_var(char **env, int i)
{
	free(env[i]);
	while (env[i] != NULL)
	{
		env[i] = env[i + 1];
		i++;
	}
	return (env);
}

static void free_env_var(char *ex_env, char *ex_var)
{
	free(ex_env);
	free(ex_var);
}

char **unset_ccc(char *var, char **env)
{
	char *ex_var;
	char *ex_env;
	int i;

	i = 0;
	ex_var = var_ex(var, '=');
	while (env[i] != NULL)
	{
		ex_env = var_ex(env[i], '=');
		if (varcmp(ex_var, ex_env, ft_strlen_g(ex_var)) == 1)
		{
			env = remove_env_var(env, i);
			free_env_var(ex_env, ex_var);
			return (env);
		}
		free(ex_env);
		i++;
	}
	free(ex_var);
	return (env);
}

void **builtin_unset(char *input, char **env)
{
	char **var;
	int i;

	i = 1;
	var = ft_split_bt(input, ' ');
	if (var[i] == NULL)
	{
		printf("unset: not enough arguments\n");
		return ((void **)env);
	}
	while (var[i] != NULL)
	{
		env = (char **)unset_ccc(var[i], env);
		i++;
	}
	mtxs_free(var);
	return ((void **)env);
}
