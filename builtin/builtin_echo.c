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

static void	print_env_value(char *var_name, char **env)
{
	int		j;
	char	*env_value;
	int		var_len;

	var_len = strlen(var_name);
	env_value = NULL;
	j = 0;
	while (env[j] != NULL)
	{
		if (strncmp(env[j], var_name, var_len) == 0 && env[j][var_len] == '=')
		{
			env_value = env[j] + var_len + 1;
			break ;
		}
		j++;
	}
	if (env_value)
		printf("%s", env_value);
}

static char	*extract_var_name(char *str, int start, int end)
{
	char	*var_name;
	var_name = (char *)malloc(sizeof(char) * (end - start + 1));
	if (var_name)
	{
		ft_memcpy(var_name, str + start, end - start);
		var_name[end - start] = '\0';
	}
	return (var_name);
}

static void	handle_dollar_sign(char *str, int *i, char **env)
{
	int		start;
	int		end;
	char	*var_name;

	if (str[*i + 1] == '?')
	{
		printf("%d", g_exit_code);
		*i += 2;
		return ;
	}
	start = *i + 1;
	end = start;
	while (is_valid_var_char(str[end]))
		end++;
	if (end > start)
	{
		var_name = extract_var_name(str, start, end);
		if (var_name)
		{
			print_env_value(var_name, env);
			free(var_name);
			*i = end;
		}
	}
}

static void	print_with_env(char *str, char **env)
{
	int	i;

	if (!str)
		return;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1])
			handle_dollar_sign(str, &i, env);
		else
			printf("%c", str[i++]);
	}
}

void	builtin_echo(char **args, char **env)
{
	int	i;
	int	option_n;

	if (!args[1])
	{
		printf("\n");
		return;
	}
	i = 1;
	option_n = 0;
	while (args[i] && check_option_n(args[i]))
	{
		option_n = 1;
		i++;
	}
	while (args[i])
	{
		if (args[i][0] != '\0')
			print_with_env(args[i], env);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!option_n)
		printf("\n");
}
