/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:54:19 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:54:19 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	control_bt(char *input, char **env)
{
	if (!input)
		return (1);
	if (ft_strncmp(input, "pwd", 3) == 0)
		return (builtin_pwd(env));
	else if (ft_strncmp(input, "cd", 2) == 0)
		return (builtin_cd(input, env));
	else if (ft_strncmp(input, "env", 3) == 0)
		return (builtin_env(env, 0));
	else if (ft_strncmp(input, "exit", 4) == 0)
		return (builtin_exit(input));
	else if (ft_strncmp(input, "export", 6) == 0)
		return (builtin_export(input, env));
	else
		return(1);
	//else if (ft_strnstr(input, "unset", 6) == 0 && ecmd->argv[1])
	//	return (builtin_unset(env, cur, ecmd->argv[1]));
	return (0);
}
