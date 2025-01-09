/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:17:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/08 15:17:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	control_bt(t_main *main, t_cmd *cur)
{
	if (!ft_strncmp(cur->cmd, "exit", 5))
		return (builtin_exit(main, cur->cmd, 4, 0));
	// else if (!ft_strncmp(cur->cmd, "pwd", 4))
	// 	return (builtin_pwd());
	// else if (!ft_strncmp(cur->cmd, "env", 4))
	// 	return (builtin_env(main->env));
	// else if (!ft_strncmp(cur->cmd, "cd", 3))
	// 	return (builtin_cd(main, cur));
	// else if (!ft_strncmp(cur->cmd, "export", 7))
	// 	return (builtin_export(main, cur));
	// else if (!ft_strncmp(cur->cmd, "unset", 6))
	// 	return (builtin_unset(main, cur));
	// else if (!ft_strncmp(cur->cmd, "echo", 5))
	// 	return (builtin_echo(cur));
	// return (0);
}

int	looking_for_env(t_main *main, char *cmd)
{
	char	**str;
	int		i;

	i = 0;
	while (main->env[i])
	{
		str = ft_split(main->env[i], '=');
		malloc_p(str);
		if (ft_matrixlen(str) >= 1 && !ft_strncmp(str[0], cmd, ft_strlen(cmd) + 1))
			return (free_matrix(str), 1);
		free_matrix(str);
		i++;
	}
	return (0);
}
