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

int	builtin_exit(char *cmd, char **env, void (*free_all)(void))
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (cmd[i] != ' ' && cmd[i] != '\0' && ft_isdigit(cmd[i]) == 1)
		i++;
	rl_clear_history();
	if (cmd[i] == ' ' || cmd[i] == '\0')
	{
		printf("exit\n");
		str = ft_substr(cmd, j, i - j);
		i = ft_atoi(str);
		free(str);
		if (free_all)
			free_all();
		free_matrix(env);
		exit (i);
	}
	else
	{
		if (free_all)
			free_all();
		free_matrix(env);
		write (2, "Panic: Numeric Value Required\n", 30);
		exit (2);
	}
	return (1);
}
