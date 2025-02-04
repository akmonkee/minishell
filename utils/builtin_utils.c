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

int is_builtin(char *cmd)
{
    if (!cmd)
        return (0);
    return (!ft_strncmp(cmd, "cd", 3) ||
            !ft_strncmp(cmd, "echo", 5) ||
            !ft_strncmp(cmd, "pwd", 4) ||
            !ft_strncmp(cmd, "export", 7) ||
            !ft_strncmp(cmd, "unset", 6) ||
            !ft_strncmp(cmd, "env", 4) ||
            !ft_strncmp(cmd, "exit", 5));
}

int control_bt(char *input, t_cmd *cur)
{
    t_execcmd *ecmd;

    if (!input || !is_builtin(input))
        return (0);

    ecmd = (t_execcmd*)cur;

    if (ft_strnstr(input, "pwd", 4) == 0)
        return (builtin_pwd());
    else if (ft_strnstr(input, "cd", 3) == 0)
        return (builtin_cd(cur, getenv("HOME"), ecmd->argv, environ));
    else if (ft_strnstr(input, "export", 7) == 0 && ecmd->argv[1])
        return (builtin_export(ecmd->argv[1]));
    else if (ft_strnstr(input, "env", 4) == 0)
        return (builtin_env(environ, 1, ecmd));
    else if (ft_strnstr(input, "exit", 5) == 0)
        return (builtin_exit(input, environ, NULL));
    else if (ft_strnstr(input, "unset", 6) == 0 && ecmd->argv[1])
        return (builtin_unset(environ, cur, ecmd->argv[1]));

    return (0);
}

// int	looking_for_env(char **env, char *cmd)
// {
// 	char	**str;
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 	{
// 		str = ft_split(env[i], '=');
// 		malloc_p(str);
// 		if (ft_matrixlen(str) >= 1 && !ft_strncmp(str[0], cmd, ft_strlen(cmd) + 1))
// 			return (free_matrix(str), 1);
// 		free_matrix(str);
// 		i++;
// 	}
// 	return (0);
// }

// char	*pick_env(char **env, char *env_var)
// {
// 	char	**str;
// 	int		i;
// 	char	*temp;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		str = ft_split(env[i], '=');
// 		if (ft_matrixlen(str) >= 2 && ft_strncmp(str[0], env_var, ft_strlen(env_var) + 1) == 0)
// 		{
// 			temp = ft_strjoin(str[1], "\0");
// 			free_matrix(str);
// 			return (temp);
// 		}
// 		free_matrix(str);
// 		i++;
// 	}
// 	temp = malloc(1);
// 	temp[0] = '\0';
// 	return (temp);
// }


// char	**order(char **matrix, int i, int j, int l)
// {
// 	char	*temp;

// 	while (i < l - 1)
// 	{
// 		j = 0;
// 		while (j < l - i - 1)
// 		{
// 			if (ft_strncmp(matrix[j], matrix[j + 1], ft_strlen(matrix[j])) > 0)
// 			{
// 				temp = matrix[j];
// 				matrix[j] = matrix[j + 1];
// 				matrix[j + 1] = temp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (matrix);
// }

// char	*extract_token(const char *cmd, int i, int j)
// {
// 	i = go_next(0, cmd);
// 	j = i;
// 	while (cmd[i] != '\0' && cmd[i] != ' ' && cmd[i] != '+' && cmd[i] != '=')
// 		i++;
// 	return (ft_substr(cmd, j, i - j));
// }

