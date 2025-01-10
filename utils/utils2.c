/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:06:06 by marvin            #+#    #+#             */
/*   Updated: 2025/01/09 17:06:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *s)
{
	int		i;
	int		res;
	int		sign;

	i = 0;
	if (ft_strncmp("-2147483648", s, 12) == 0)
		return (-2147483648);
	if (s == NULL)
		return (0);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i] - '0');
		i++;
	}
	return (res * sign);
}

int	skip_space(int i, char *str)
{
	if (str == NULL)
		return (i);
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			break ;
	}
	return (i);
}
