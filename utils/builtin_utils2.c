/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:19:49 by msisto            #+#    #+#             */
/*   Updated: 2025/03/27 14:29:55 by msisto           ###   ########.fr       */
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
	while(ret != 1 && ++i < ft_strlen_g(ex_in))
		if (ex_in[i] != sample[i])
			ret = 1;
	free(ex_in);
	return (ret);
}

char	**env_cloner(char **envp)
{
	char	**ret;
	int		i;

	i = -1;
	while (envp[++i] != NULL)
		;
	ret = malloc((i + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = -1;
	while (envp[++i] != NULL)
		ret[i] = var_ex(envp[i], '\0');
	ret[i] = NULL;
	return (ret);
}
