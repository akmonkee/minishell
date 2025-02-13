/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:53:48 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:53:48 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	export_ccc(char *var, char **env)
{
	char	*ex_var;
	char	*ex_env;
	int		i;
	int		k;

	i = 0;
	ex_var = var_ex(var, '=');
	while (env[i] != NULL)
	{
		ex_env = var_ex(env[i], '=');
		if (varcmp(ex_var, ex_env, ft_strlen_g(ex_var)) == 1)
		{
			free(env[i]);
			env[i] = malloc(ft_strlen_g(var) + 1);
			k = 0;
			while (var[k])
			{
				env[i][k] = var[k];
				k++;
			}
			env[i][k] = '\0';
		}
		free(ex_env);
		i++;
	}
	free(ex_var);
}

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
	int		i;

	i = 1;
	var = ft_split(input, ' ', 0, 0);
	if (var[i] == NULL)
	{
		builtin_env(env, 1);
		mtxs_free(var);
		return (0);
	}
	while (var[i] != NULL)
	{
		if (ft_strnstr(var[i], "=", ft_strlen_g(var[i])) != 0)
			export_ccc(var[i], env);
		i++;
	}
	//tmp = ft_realloc(env, mtx_len(env) + mtx_len(var));
	//while (i < mtx_len(var))
	//{
	//	var_extractor(var[i], tmp[mtx_len(tmp) - mtx_len(var) + i]);
	//	i++;
	//}
	//env = tmp;
	mtxs_free(var);
	return (0);
}
