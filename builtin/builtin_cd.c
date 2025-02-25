/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:55 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:55 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	**builtin_cd(char *input, char **env)
{
	while (*input != 92 && *input != '\0')
		input++;
	chdir(input);
	if (chdir(input) == -1)
	{
		printf("cd: %s: No such file or directory\n", input);
		return (NULL);
	}
	return (NULL);
}

