/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:22:39 by msisto            #+#    #+#             */
/*   Updated: 2024/12/02 11:32:30 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *comp, char *s)
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

size_t	ft_strlen(char	*s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
