/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:05:25 by msisto            #+#    #+#             */
/*   Updated: 2025/05/07 10:05:25 by msisto           ###   ########.fr       */
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
	ex_var = var_ex(var, '\0');
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
	g_exit_code = 0;
	return ;
}
