/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:49:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 15:49:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_main *main, t_cmd *cur)
{
	int	i;
	char	**str;
	char	*temp;
	char	**arg;

	i = 0;
	arg = take_args(cur->cmd, main, cur);
	while (main->env[i] && main->print == 1)
	{
		str = ft_split(main->env[i], '=');
		temp = pick_env(main, str[0]);
		if (temp)
			printf("%s\n", main->env[i]);
		free(temp);
		free_matrix(str);
		i++;
	}
	free_matrix(arg);
	return (1);
}

void	env2(t_main *main, int i)
{
	char	**str;
	char	**matrix;

	matrix = order(copy_matrix(main->env), 0, 0, ft_matrixlen(main->env));
	while (matrix[i])
	{
		str = ft_split(matrix[i], '=');
		if (ft_matrixlen(str) == 1)
			printf("declare -x %s\n", str[0]);
		else
			printf("declare -x %s=\"%s\"\n", str[0], str[1]);
		free_matrix(str);
		i++;
	}
	free_matrix(matrix);
}
