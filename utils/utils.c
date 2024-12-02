/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:22:39 by msisto            #+#    #+#             */
/*   Updated: 2024/12/02 14:09:58 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *s, char *comp)
{
	int	i;
	int	k;

	i = 0;
	while (s[i])
	{
		k = 0;
		while (comp[k])
		{
			if (s[i] == comp[k])
				return (1);
			k++;
		}
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
