/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:14:25 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 16:14:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_exit(t_main *main, char *cmd, int i, int j)
{
	char	*str;

	j = i;
	while(cmd[i] != ' ' && cmd[i] != '\0' && ft_isdigit(cmd[i]))
		i++;
	rl_clear_history();
	if (cmd[i] == ' ' || cmd[i] == '\0')
	{
		printf("exit\n");
		str = ft_substr(cmd, j, i - j);
		i = ft_atoi(str);
		free(str);
		free_all(main);
		free_matrix(main->env);
		exit(i);
	}
	else
	{
		free_all(main);
		free_matrix(main->env);
		write(2, "Panic: Numeric Value required\n", 30);
		g_code_exit = 2;
		exit(2);
	}
	return (1);
}
