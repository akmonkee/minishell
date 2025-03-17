/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 11:19:49 by msisto            #+#    #+#             */
/*   Updated: 2025/03/17 12:57:21 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
