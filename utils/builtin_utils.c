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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_g(s))
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	**execute_builtin(char **args, char *input, char **env)
{
	char	**tmp;

	tmp = NULL;
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		builtin_pwd(env);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		tmp = (char **)builtin_cd(input, env);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		builtin_echo(args, env);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		builtin_env(env);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		builtin_exit(input);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		tmp = (char **)builtin_export(input, env);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		builtin_unset(input, env);
	return (tmp);
}

void	**exe_bt(char *input, char **env)
{
	char	**tmp;
	char	**args;

	if (!input)
		return (NULL);
	args = ft_split_bt(input, ' ');
	if (!args)
		return (NULL);
	tmp = execute_builtin(args, input, env);
	mtxs_free(args);
	return ((void **)tmp);
}

static int	check_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	return (0);
}

int	control_bt(char *input, char **env)
{
	char	**args;
	int		ret;

	ret = 0;
	if (!input)
		return (1);
	args = ft_split_bt(input, ' ');
	if (!args)
		return (1);
	ret = check_builtin(args[0]);
	mtxs_free(args);
	return (ret);
}
