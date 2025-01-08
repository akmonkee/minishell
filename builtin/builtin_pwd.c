/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:02:24 by marvin            #+#    #+#             */
/*   Updated: 2025/01/08 11:02:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd("pwd: error retrieving current directory: No such file or directory\n", 2);
		return (0);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
}
