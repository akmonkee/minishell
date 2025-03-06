/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 13:50:08 by msisto            #+#    #+#             */
/*   Updated: 2025/03/05 13:50:39 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	p_export(char **env_cp)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (env_cp[++i])
	{
		len = -1;
		while (env_cp[i][++len] && env_cp[i][len] != '=')
			;
		j = -1;
		printf("declare -x ");
		while (++j < len)
			printf("%c", env_cp[i][j]);
		if (len < ft_strlen_g(env_cp[i]) && ft_strchr(env_cp[i], '='))
			printf("=\"%s\"", env_cp[i] + len + 1);
		printf("\n");
	}
}

void	sort_env(char **env)
{
	int		i;
	int		k;
	int		size;
	char	*tmp;
	char	**env_cp;

	size = mtx_len(env);
	env_cp = env_cloner(env);
	i = -1;
	while (++i < size - 1)
	{
		k = -1;
		while (++k < size - i - 1)
		{
			if (strcmp(env_cp[k], env_cp[k + 1]) > 0)
			{
				tmp = env_cp[k];
				env_cp[k] = env_cp[k + 1];
				env_cp[k + 1] = tmp;
			}
		}
	}
	p_export(env_cp);
	mtxs_free(env_cp);
}
