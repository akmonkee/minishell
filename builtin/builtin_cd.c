/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 15:01:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/13 15:01:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int builtin_cd(char *input, char **env)
{
	while (*input != 92 && *input != '\0')
		input++;
	chdir(input);
	if (chdir(input) == -1)
	{
		printf("cd: %s: No such file or directory\n", input);
		return (1);
	}
	return (0);
}

