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

static char *supp_export2(t_main *main, t_cmd *cur, char *env, int i)
{
	int		j;
	char	*temp;

	while (cur->cmd[i] && cur->cmd[i] != '=' && cur->cmd[i] != '+')
		i++;
	if (cur->cmd[i] == '+')
	{
		i += 2;
		j = supp_export1(cur, &i);
		return (ft_strjoin12f(pick_env(main, env), ft_substr(cur->cmd, j, i - j)));
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

static char	**supp_export3(t_main *main, t_cmd *cur, char *env, int i)
{
	char	**matrix;

	matrix = malloc((ft_matrixlen(main->env) + 2) * sizeof(char *));
	malloc_p(matrix);
	while (main->env[++i] != NULL)
		matrix[i] = ft_strjoin(main->env[i], "\0");
	matrix[i] = ft_strjoin12f(ft_strjoin(env, "="), supp_export2(main, cur, env, go_next(0, cur->cmd)));
	i++;
	matrix[i] = NULL;
	free_matrix(main->env);
	return (matrix);
}

int	builtin_export(t_main *main, t_cmd *cur, t_data2 data)
{
	char	**matrix;

	data.arg = take_args(cur->cmd, main, cur);
	if (malloc_p(data.arg) != 0 && ft_matrixlen(data.arg) > 1 && looking_for_env(main, data.t1) == 0)
		main->env = supp_export3(main, cur, data.t1, data.i);
	else if (malloc_p(data.arg) != 0 && ft_matrixlen(data.arg) == 1 && main->print == 1)
		env2(main, 0);
	else
	{
		while (main->env[++data.i] != NULL)
		{
			matrix = ft_split(main->env[data.i], '=');
			if (ft_strncmp(matrix[0], data.t1, ft_strlen(data.t1) + 1) == 0)
			{
				data.t2 = ft_strjoin12f(ft_strjoin(data.t1, "="),
					supp_export2(main, cur, data.t1, go_next(0, cur->cmd)));
				free(main->env[data.i]);
				main->env[data.i] = ft_strjoin1f(data.t2, "\0");
			}
			free_matrix(matrix);
		}
	}
	free_matrix(data.arg);
	free(data.t1);
	return (1);
}
