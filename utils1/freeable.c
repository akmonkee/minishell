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

void	free_all(t_cmd *lcmd, char *input, int *ncmd)
{
	t_cmd	*cur;
	t_cmd	*next;

	cur = lcmd;
	while (cur)
	{
		free(cur->cmd);
		next = cur->next;
		cur = next;
	}
	if (input)
		free(input);
	if (ncmd)
		*ncmd = 0;
}


int	super_free(t_cmd *lcmd, char *input, int *ncmd, char **env, int in, int out)
{
	free_all(lcmd, input, ncmd);
	rl_clear_history();
	free_matrix(env);
	close(in);
	close(out);

	return (0);
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
