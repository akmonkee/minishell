/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_quoted_arg.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:43:48 by msisto            #+#    #+#             */
/*   Updated: 2025/04/14 13:44:25 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	**be_ll(char *ret, char **tmp)
{
	char	*ex_var;
	char	*ex_env;
	int		k;

	k = -1;
	ex_var = var_ex(ret, '=');
	while (tmp[++k] != NULL)
	{
		ex_env = var_ex(tmp[k], '=');
		if (varcmp(ex_var, ex_env, ft_strlen_g(ex_var)) == 1)
		{
			tmp[k] = a_var_update(ret, tmp[k], tmp);
			free(ex_env);
			free(ex_var);
			free(ret);
			return ((void **)tmp);
		}
		free(ex_env);
	}
	free(ex_var);
	tmp = (char **)ft_realloc(tmp, mtx_len(tmp) + 1);
	tmp[mtx_len(tmp)] = NULL;
	tmp[mtx_len(tmp)] = ret;
	return ((void **)tmp);
}
