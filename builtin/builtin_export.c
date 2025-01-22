/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:16:06 by marvin            #+#    #+#             */
/*   Updated: 2025/01/13 14:16:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	supp_export1(t_cmd *cur, int *i)
{
	int	j;

	if (cur->cmd[*i] == '\'' || cur->cmd[*i] == '\"')
	{
		(*i)++;
		j = *i;
		while (cur->cmd[j] != '\0' && cur->cmd[j] != '\'' && cur->cmd[j] != '\"')
			(*i)++;
	}
	else
	{
		j = *i;
		while (cur->cmd[*i] != '\0' && cur->cmd[*i] != ' ')
			(*i)++;
	}
	return (j);
}

static char	*supp_export2(char **env, t_cmd *cur, char *env_name, int i)
{
	int		j;
	char	*temp;

	while (cur->cmd[i] && cur->cmd[i] != '=' && cur->cmd[i] != '+')
		i++;
	if (cur->cmd[i] == '+')
	{
		i += 2;
		j = supp_export1(cur, &i);
		return (ft_strjoin12f(pick_env(env, env_name), ft_substr(cur->cmd, j, i - j)));
	}
	else if (cur->cmd[i] == '=')
	{
		i += 1;
		j = supp_export1(cur, &i);
		return (ft_substr(cur->cmd, j, i - j));
	}
	temp = malloc(1);
	temp[0] = '\0';
	return (temp);
}

static char **supp_export3(char **env, t_cmd *cur, char *env_name, int i)
{
	char	**matrix;

	matrix = malloc((ft_matrixlen(env) + 2) * sizeof(char *));
	malloc_p(matrix);
	while (env[++i] != NULL)
		matrix[i] = ft_strjoin(env[i], "\0");
	matrix[i] = ft_strjoin12f(ft_strjoin(env_name, "="), supp_export2(env, cur, env_name, go_next(0, cur->cmd)));
	i++;
	matrix[i] = NULL;
	free_matrix(env);
	return (matrix);
}

int builtin_export(char **env, t_cmd *cur)
{
	char	**matrix;
	char	*env_name;
	char	**args;
	int		i;

	i = 0;
	args = take_args(cur, cur->cmd);
	if (malloc_p(args) != 0 && ft_matrixlen(args) > 1 && looking_for_env(env, args[0]) == 0)
		env = supp_export3(env, cur, args[0], i);
	else if (malloc_p(args) != 0 && ft_matrixlen(args) == 1)
		env2(env, 0);
	else
	{
		while (env[++i] != NULL)
		{
			matrix = ft_split(env[i], '=');
			if (ft_strncmp(matrix[0], args[0], ft_strlen(args[0]) + 1) == 0)
			{
				env_name = ft_strjoin12f(ft_strjoin(args[0], "="),
					supp_export2(env, cur, args[0], go_next(0, cur->cmd)));
				free(env[i]);
				env[i] = ft_strjoin1f(env_name, "\0");
			}
			free_matrix(matrix);
		}
	}
	free_matrix(args);
	return (1);
}
