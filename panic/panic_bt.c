/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic_bt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:51:07 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 16:51:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	malloc_p(char **m)
{
	if (m == NULL)
	{
		return (0);
		perror("Panic: Malloc error");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	file_p(char *file, int cmd)
{
	int	fd;

	fd = -1;
	if (cmd == 1)
		fd = open(file, O_RDONLY);
	else if (cmd == 3)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (cmd == 4)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		perror("Panic: open error");
		exit(EXIT_FAILURE);
	}
	return (fd);
}
