/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:22:39 by msisto            #+#    #+#             */
/*   Updated: 2025/01/08 10:56:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *comp, char s)
{
	int	i;
	int	k;

	i = 0;
	while (comp[i])
	{
		if (s == comp[i])
			return (1);
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

void	*ft_memset(void *b, int c, size_t len)
{
	char	*s;
	size_t	i;

	s = NULL;
	s = (char *)b;
	i = 0;
	while (i < len)
	{
		s[i] = c;
		i++;
	}
	return (b);
}

ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
