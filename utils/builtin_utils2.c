/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:19:49 by msisto            #+#    #+#             */
/*   Updated: 2025/03/14 17:56:00 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_g(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	builtin_exec(char **command, char **envp)
{
	if (ft_strncmp(command[0], "pwd", 3) == 0)
	{
		if (command[1] != NULL)
		{
			perror("too many args\n");
			g_exit_code = 1;
		}
		else
			return (builtin_pwd(envp), 1);
	}
	else if (ft_strncmp(command[0], "env", 3) == 0)
	{
		if (command[1] != NULL)
		{
			perror("too many args\n");
			g_exit_code = 1;
		}
		else
			return (builtin_env(envp), 1);
	}
	else if (ft_strncmp(command[0], "echo", 4) == 0)
		return(builtin_echo(command), 1);
	return (g_exit_code);
}

char	**env_cloner(char **envp)
{
	char	**ret;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
		;
	ret = malloc((i + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (envp[++i] != NULL)
		ret[i] = var_ex(envp[i], '\0');
	ret[i] = NULL;
	return (ret);
}
