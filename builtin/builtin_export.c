/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:05 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:05 by efoschi          ###   ########.fr       */
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

void	var_extractor(char *var, char *input)
{
	int	i;

	i = 0;
	input = malloc(ft_strlen(var) + 1);
	if (input == NULL)
		return ;
	while (var[i] != '\0')
	{
		input[i] = var[i];
		i++;
	}
}

int	builtin_export(char *input, char **env)
{
	char	**var;
	char	**tmp;
	char	*check;
	int		i;

	i = 0;
	var = ft_split(input, ' ', 0, 0);
	if (var[1] == NULL)
	{
		builtin_env(env, 1);
		return (0);
	}
	if (ft_strnstr(var[i], "=", 1) != 0)
		return (1);
	check = name_extractor(var[i], ft_strchr(var[i], '='));
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], check, ft_strlen(check)) == 0)
			break ;
		i++;
	}
	tmp = ft_realloc(env, mtx_len(env) + mtx_len(var));
	while (i < mtx_len(var))
	{
		var_extractor(var[i], tmp[mtx_len(tmp) - mtx_len(var) + i]);
		i++;
	}
	env = tmp;
	mtxs_free(var);
	return (0);
}
