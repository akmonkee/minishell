/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:58:10 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 14:58:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_pwd(char **envp)
{
	char	**var;
	int		i;

	i = 0;
	while (!ft_strnstr(envp[i], "PWD", 3))
		i++;
	var = ft_split (envp[i], '=', 0, 0);
	printf("%s\n", var[1]);
	mtxs_free(var);
}
