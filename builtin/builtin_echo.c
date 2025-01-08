/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 10:18:53 by marvin            #+#    #+#             */
/*   Updated: 2025/01/08 10:18:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **cmd)
{
	int	flag;

	cmd++;
	flag = 0;
	while (*cmd && check_option(*cmd))
	{
		flag = 1;
		cmd++;
	}
	while (*cmd)
	{
		ft_putstr_fd(*cmd, 1);
		cmd++;
		if (*cmd)
			ft_putstr_fd(" ", 1);
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	//exit_with_status(0);
}
