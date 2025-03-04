/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_is_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:07:26 by msisto            #+#    #+#             */
/*   Updated: 2025/03/04 15:08:02 by msisto           ###   ########.fr       */
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
	int	i;

	i = -1;
	if (!ft_isalpha(arg[0]))
	{
		perror("not a valid identifier\n");
		g_exit_code = 1;
		return (0);
	}
	while (arg[++i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '=' && arg[i] != '+')
		{
			perror("not a valid identifier\n");
			g_exit_code = 1;
			return (0);
		}
		else if (arg[i] == '=')
			return (1);
	}
	return (0);
}
