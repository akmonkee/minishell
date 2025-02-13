/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:54:31 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:54:31 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_ex(char *str, char c)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	ret = malloc(i + 1);
	if (!ret)
		return(NULL);
	i = 0;
	while (str[i] != c)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

int	varcmp(char *str1, char *str2, int n)
{
	int		i;

	i = 0;
	if (!n)
		return (0);
	if (ft_strlen_g(str1) > ft_strlen_g(str2))
		return (0);
	if (ft_strlen_g(str1) < ft_strlen_g(str2))
		return (0);
	while (str1[i] == str2[i] && i < n && str1[i] && str2[i])
		i++;
	if (str1[i] != str2[i])
		return(0);
	else
		return (1);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] && s2[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
