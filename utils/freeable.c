/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 16:23:33 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 16:23:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_main *main)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = main->lcmd;
	while (cur->next)
	{
		free(cur->cmd);
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(cur->cmd);
	free(cur);
	main->lcmd = NULL;
	free(main->input);
	main->ncmd = 0;
}

int	free_matrix(char **matrix)
{
	int	i;


	if (matrix == NULL)
		return (0);
	if (matrix != NULL)
	{
		i = 0;
		while (matrix[i] != NULL)
		{
			if (matrix[i] != NULL)
			{
				free(matrix[i]);
				matrix[i] = NULL;
			}
			i++;
		}
		free(matrix);
		matrix = NULL;
	}
	return (0);
}

int	free_str(char *str)
{
	free(str);
	return (0);
}
