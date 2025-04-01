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

void	remove_env_var(char **env, int i)
{
	char	*tmp;
	while (env[i + 1] != NULL)
	{
		tmp = env[i];
		env[i] = env[i + 1];
		env[i + 1] = tmp;
		i++;
	}
	free(env[i]);
	env[i] = NULL;
}

void	free_env_var(char *ex_env, char *ex_var)
{
	free(ex_env);
	free(ex_var);
}

void	unset_ccc(char *var, char **env)
{
	char	*ex_var;
	char	*ex_env;
	int		i;

	i = 1;
	ex_var = var_ex(var, '=');
	while (env[i] != NULL)
	{
		ex_env = var_ex(env[i], '=');
		if (varcmp(ex_var, ex_env, ft_strlen_g(ex_var)) == 1)
		{
			remove_env_var(env, i);
			free_env_var(ex_env, ex_var);
			return ;
		}
		free(ex_env);
		i++;
	}
	free(ex_var);
	return ;
}

void	builtin_unset(char **input, t_mini *mini)
{
	int		i;

	i = 1;
	if (!mini->env)
		return ;
	if (input[i] == NULL)
		return ;
	while (input[i] != NULL)
	{
		unset_ccc(input[i], mini->env);
		i++;
	}
	return ;
}
