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
	char	*str;

	str = no_space(cur->cmd);
	if (ft_strncmp(str, "exit", 5) == 0 && free_str(str))
		return (builtin_exit(main, cur->cmd, go_next(0, cur->cmd), 0));
	if (ft_strncmp(str, "env", 4) == 0 && free_str(str))
		return (builtin_env(main, cur));
	if (ft_strncmp(str, "export", 7) == 0 && free_str(str))
		return (builtin_export(main, cur, (t_data2){NULL, extract_token(cur, 0, 0), 0, -1}));
	if (ft_strncmp(str, "unset", 6) == 0 && free_str(str))
		return (1);
	if (ft_strncmp(str, "cd", 3) == 0 && free_str(str))
		return (1);
	if (ft_strncmp(str, "pwd", 4) == 0 && free_str(str))
		return (builtin_pwd());
	free(str);
	return (0);
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

char	*pick_env(t_main *main, char *env)
{
	char	**str;
	int		i;
	char	*temp;

	i = 0;
	while (main->env[i] != NULL)
	{
		str = ft_split(main->env[i], '=');
		if (ft_matrixlen(main->env) >= 2 && ft_strncmp(str[0], env, ft_strlen(env) + 1) == 0)
		{
			temp = ft_strjoin(str[1], "\0");
			free_matrix(str);
			return (temp);
		}
		free_matrix(str);
		i++;
	}
	temp = malloc (1);
	temp[0] = '\0';
	return (temp);
}

char	**order(char **matrix, int i, int j, int l)
{
	char	*temp;

	while (i < l - 1)
	{
		j = 0;
		while (j < l - i - 1)
		{
			if (ft_strncmp(matrix[j], matrix[j + 1], ft_strlen(matrix[j])) > 0)
			{
				temp = matrix[j];
				matrix[j] = matrix[j + 1];
				matrix[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
	return (matrix);
}

char	*extract_token(t_cmd *cur, int i, int j)
{
	i = go_next(0, cur->cmd);
	j = i;
	while (cur->cmd[i] != '\0' && cur->cmd[i] != ' ' && cur->cmd[i] != '+' && cur->cmd[i] != '=')
		i++;
	return (ft_substr(cur->cmd, j, i - j));
}
