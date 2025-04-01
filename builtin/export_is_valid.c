/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_is_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:07:26 by msisto            #+#    #+#             */
/*   Updated: 2025/04/01 13:44:51 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

int	arg_validation(char	*arg)
{
	char	*name;
	int	i;

	i = -1;
	name = var_ex(arg, '=');
	if (!ft_isalpha(arg[0]))
	{
		panic_fun(name, ": not a valid identifier\n", 1, 0);
		return (free(name), 0);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=' && arg[i] != '+')
		{
			panic_fun(name, ": not a valid identifier\n", 1, 0);
			return (free(name), 0);
		}
		else if (arg[i] == '=')
			return (free(name), 1);
	}
	return (free(name), 0);
}

static int	size(int num)
{
	int	len;

	len = 0;
	if (num == 0)
		len++;
	if (num < 0)
		len++;
	while (num)
	{
		len++;
		num /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*out;
	int		len;

	len = size(n);
	out = malloc(len + 1);
	if (!out)
		return (NULL);
	out[len] = '\0';
	if (n < 0)
		out[0] = '-';
	else if (n < 10 && n >= 0)
	{
		out[0] = n + 48;
		return (out);
	}
	while (len-- > 0 && n)
	{
		if (n < 0)
			out[len] = (-(n % 10)) + 48;
		else
			out[len] = (n % 10) + 48;
		n /= 10;
	}
	return (out);
}
