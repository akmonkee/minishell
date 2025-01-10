/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:49:35 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 15:49:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_main *main, t_cmd *cur)
{
	int	i;
	char	**str;
	char	*temp;
	char	**arg;

	i = 0;
	arg = take_args(cur->cmd, main, cur);
	while (main->env[i] && main->print == 1)
	{
		str = ft_split(main->env[i], '=');
		temp = pick_env(main, str[0]);
		if (temp)
			printf("%s\n", main->env[i]);
		free(temp);
		free_matrix(str);
		i++;
	}
	free_matrix(arg);
	return (1);
}
