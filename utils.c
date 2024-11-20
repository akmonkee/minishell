/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:44:15 by msisto            #+#    #+#             */
/*   Updated: 2024/11/20 12:17:07 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
		i++;
	return (i);
}

char	*home_set(char *input)
{
	int		i;
	int		j;
	char	*out;

	i = 5;
	j = ft_strlen(input) - i;
	out = malloc((j + 1) * sizeof(char));
	j = 0;
	while (input[i + j] != '\0')
	{
		out[j] = input[i + j];
		j++;
	}
	out[j] = '\0';
	return (out);
}

int	ft_strcmp(char *input, char *cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((input[i] && cmd[j]))
	{
		if (input[i] != cmd[j])
			return (1);
		if (!cmd[j])
			return (0);
		j++;
		i++;
	}
	return (0);
}
