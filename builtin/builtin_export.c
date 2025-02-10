/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:12:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/24 11:12:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_realloc(char **mtx, int size)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc((size + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	while (i < size)
	{
		ret[i] = mtx[i];
		i++;
	}
	ret[i] = NULL;
	mtxs_free(mtx);
	return (ret);
}

int	builtin_export(char *input, char **env)
{
	char	**var;
	int		i;

	i = 0;
	var = ft_split(input, ' ', 0, 0);
	if (var[1] == NULL)
	{
		builtin_env(env, 1);
		return (0);
	}
	env = ft_realloc(env, mtx_len(env) + mtx_len(var));
	while (i < mtx_len(var))
	{
		env[mtx_len(env) - mtx_len(var) + i] = var[i];
		i++;
	}
}
