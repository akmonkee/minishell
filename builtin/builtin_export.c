/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:07:11 by marvin            #+#    #+#             */
/*   Updated: 2025/01/08 11:07:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_export(char **cmd)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (cmd[i])
	{
		key = cmd[i];
		value = ft_strchr(cmd[i], '=');
		if (value)
		{
			*value = 0;
			value++;
		}
		if (key && value)
			setenv(key, value, 1);
		else if (key)
			setenv(key, "", 1);
		i++;
	}
}
