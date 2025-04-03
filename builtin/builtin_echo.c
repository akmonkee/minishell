/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:18 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:18 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_option_n(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] != '-')
		return (0);
	i++;
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

void	print_with_env(char **arg, int i, char **env)
{
	char	*elab;

	elab = NULL;
	while (arg[i])
	{
		if (arg[i][0] != '\0')
		{
			elab = var_content_elab(arg[i], env);
			printf ("%s", elab);
			free(elab);
		}
		if (arg[i + 1])
			printf(" ");
		i++;
	}
}

void	builtin_echo(char **args, char **env)
{
	int	i;
	int	option_n;

	if (!env)
		return ;
	if (!args[1])
	{
		printf("\n");
		return ;
	}
	i = 0;
	option_n = 0;
	while (args[++i] && check_option_n(args[i]))
		option_n = 1;
	print_with_env(args, i, env);
	if (!option_n)
		printf("\n");
	return ;
}
