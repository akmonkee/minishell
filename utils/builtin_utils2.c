/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:19:49 by msisto            #+#    #+#             */
/*   Updated: 2025/05/20 17:59:50 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	move_t_point(char *var_c, int *k, int flag)
{
	int	i;

	i = *k;
	if (flag != '\0')
	{
		while (var_c[++i] && var_c[i] != flag)
			;
	}
	else
	{
		while (var_c[++i] && var_c[i] != what_is_next(var_c + i, 0))
			if (var_c[i + 1] == 0)
				break ;
	}
	*k = i;
}

int	ft_strlen_g(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	fullcmp(char *input, char *sample)
{
	char	*ex_in;
	int		i;
	int		ret;

	i = -1;
	ret = 0;
	ex_in = var_ex(input, ' ');
	if (ft_strlen_g(sample) != ft_strlen_g(ex_in))
		ret = 1;
	while (ret != 1 && ++i < ft_strlen_g(ex_in))
		if (ex_in[i] != sample[i])
			ret = 1;
	free(ex_in);
	return (ret);
}

static void	shlvl_update(char **env, int i)
{
	char	*nbr;
	char	*cmp;
	int		lvl;

	nbr = ambient_value("$SHLVL", env);
	lvl = ft_atoi(nbr);
	free(nbr);
	nbr = ft_itoa(++lvl);
	nbr = ft_strjoinf2("SHLVL=", nbr);
	while (env[++i] != NULL)
	{
		cmp = var_ex(env[i], '=');
		if (varcmp(cmp, "SHLVL", 5))
		{
			free(env[i]);
			env[i] = var_ex(nbr, '\0');
		}
		free(cmp);
	}
	free(nbr);
}

char	**env_cloner(char **envp, int flag)
{
	char	**ret;
	int		i;

	i = mtx_len(envp);
	ret = malloc((i + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (envp[++i] != NULL)
		ret[i] = var_ex(envp[i], '\0');
	ret[i] = NULL;
	if (flag == 1)
		shlvl_update(ret, -1);
	return (ret);
}
