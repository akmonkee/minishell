/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:01:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/13 15:01:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_cd(t_cmd *cur, char *home, char **arg, char **env)
{
	free(cur->cmd);
	cur->cmd = ft_strjoin2f("export OLDPWD=", get_path());
	builtin_export(env, cur, (t_data2){0, extract_token(cur, 0, 0), 0, -1});
	if (malloc_p(arg) == 1 && ft_matrixlen(arg) == 2)
	{
		if (chdir(arg[1]) != 0)
		{
			write(2, "Panic: Unable to change directory\n", 32);
			return (1);
		}
	}
	else if (malloc_p(arg) == 1 && ft_matrixlen(arg) == 1)
	{
		if (chdir(home) != 0)
		{
			write(2, "Panic: Unable to change to home directory\n", 41);
			return (1);
		}
	}
	free(cur->cmd);
	cur->cmd = ft_strjoin2f("export PWD=", get_path());
	builtin_export(env, cur, (t_data2){0, extract_token(cur, 0, 0), 0, -1});
	free(cur->cmd);
	cur->cmd = ft_strjoin("cd", "\0");
	free_matrix(arg);
	free(home);
	return (1);
}

