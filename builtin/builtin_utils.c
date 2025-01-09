/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:17:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/08 15:17:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	control_bt(char *input, char **envp)
{
	if (!ft_strncmp(input, "cd", 2))
		return (1);
	if (!ft_strncmp(input, "pwd", 3))
		return (builtin_pwd());
	if (!ft_strncmp(input, "echo", 4))
		return (1);
	if (!ft_strncmp(input, "export", 6))
		return (1);
	if (!ft_strncmp(input, "unset", 5))
		return (1);
	if (!ft_strncmp(input, "env", 3))
		return (1);
	if (!ft_strncmp(input, "exit", 4))
		return (1);
	return (0);
}
