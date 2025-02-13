/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:53:56 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:53:56 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_pwd(char **envp)
{
	char	**var;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PWD", 3))
		i++;
	var = ft_split (envp[i], '=', 0, 0);
	printf("%s\n", var[1]);
	mtxs_free(var);
	return (0);
}
