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

// static int	supp_export1(t_cmd *cmd, int *i)
// {
// 	int	j;

// 	if (cmd->cmd[*i] == '\'' || cmd->cmd[*i] == '\"')
// 	{
// 		(*i)++;
// 		j = *i;
// 		while (cmd->cmd[j] != '\0' && cmd->cmd[j] != '\'' && cmd->cmd[j] != '\"')
// 			(*i)++;
// 	}
// 	else
// 	{
// 		j = *i;
// 		while (cmd->cmd[*i] != '\0' && cmd->cmd[*i] != ' ')
// 			(*i)++;
// 	}
// 	return (j);
// }

// static char	*supp_export2(char **env, t_cmd *cmd, char *env_name, int i)
// {
// 	int		j;
// 	char	*temp;

// 	while (cmd->cmd[i] && cmd->cmd[i] != '=' && cmd->cmd[i] != '+')
// 		i++;
// 	if (cmd->cmd[i] == '+')
// 	{
// 		i += 2;
// 		j = supp_export1(cmd, &i);
// 		return (ft_strjoin12f(pick_env(env, env_name), ft_substr(cmd->cmd, j, i - j)));
// 	}
// 	else if (cmd->cmd[i] == '=')
// 	{
// 		i += 1;
// 		j = supp_export1(cmd, &i);
// 		return (ft_substr(cmd->cmd, j, i - j));
// 	}
// 	temp = malloc(1);
// 	temp[0] = '\0';
// 	return (temp);
// }

// static char **supp_export3(char **env, t_cmd *cmd, char *env_name, int i)
// {
// 	char	**matrix;

// 	matrix = malloc((ft_matrixlen(env) + 2) * sizeof(char *));
// 	malloc_p(matrix);
// 	while (env[++i] != NULL)
// 		matrix[i] = ft_strjoin(env[i], "\0");
// 	matrix[i] = ft_strjoin12f(ft_strjoin(env_name, "="), supp_export2(env, cmd, env_name, go_next(0, cmd->cmd)));
// 	i++;
// 	matrix[i] = NULL;
// 	free_matrix(env);
// 	return (matrix);
// }

// int builtin_export(char **env, t_cmd *cmd)
// {
// 	char	**matrix;
// 	char	*env_name;
// 	char	**args;
// 	int		i;

// 	i = 0;
// 	args = take_args(cmd, cmd->cmd);
// 	if (malloc_p(args) != 0 && ft_matrixlen(args) > 1 && looking_for_env(env, args[0]) == 0)
// 		env = supp_export3(env, cmd, args[0], i);
// 	else if (malloc_p(args) != 0 && ft_matrixlen(args) == 1)
// 		env2(env, 0);
// 	else
// 	{
// 		while (env[++i] != NULL)
// 		{
// 			matrix = ft_split(env[i], '=');
// 			if (ft_strncmp(matrix[0], args[0], ft_strlen(args[0]) + 1) == 0)
// 			{
// 				env_name = ft_strjoin12f(ft_strjoin(args[0], "="),
// 					supp_export2(env, cmd, args[0], go_next(0, cmd->cmd)));
// 				free(env[i]);
// 				env[i] = ft_strjoin1f(env_name, "\0");
// 			}
// 			free_matrix(matrix);
// 		}
// 	}
// 	free_matrix(args);
// 	return (1);
// }

