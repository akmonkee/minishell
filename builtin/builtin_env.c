/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 10:04:27 by msisto            #+#    #+#             */
/*   Updated: 2025/05/07 10:04:27 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	**env_mod(char *path, char *curr_pwd, char **env)
{
	char	*path_c;
	char	*old_pwd;
	char	**ret_env;

	path_c = ft_strjoinf2("PWD=", path);
	old_pwd = ft_strjoinf2("OLDPWD=", curr_pwd);
	ret_env = env_cloner(env);
	ret_env = (char **)pwd_mod(path_c, ret_env);
	ret_env = (char **)pwd_mod(old_pwd, ret_env);
	free(path_c);
	free(old_pwd);
	return ((void **)ret_env);
}

void	env_bt(char *input, t_mini *mini)
{
	if (input)
		panic_fun("env: ", input, 127, 0);
	else
		builtin_env(mini->env);
}

void	builtin_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			printf("%s\n", env[i]);
		i++;
	}
	g_exit_code = 0;
	return ;
}
