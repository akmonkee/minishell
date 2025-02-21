/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:59:21 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:59:21 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(char **envp)
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
