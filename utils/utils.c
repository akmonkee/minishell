/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 12:00:06 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 12:00:07 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*name_extractor(char *q, char *eq)
{
	int		i;
	char	*ret;
	char	*start;

	i = 0;
	start = q;
	while (start != eq)
	{
		i++;
		start++;
	}
	start = q;
	ret = malloc(i + 1);
	i = 0;
	while (start != eq)
	{
		ret[i] = *start;
		i++;
		start++;
	}
	ret[i] = '\0';
	return (ret);
}

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

int	mtx_len(char **mtx)
{
	int	i;

	i = 0;
	while (mtx[i])
		i++;
	return (i);
}
