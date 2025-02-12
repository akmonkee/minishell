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

static int check_option_n(char *str)
{
	int i;

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

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptr1;
	const unsigned char	*ptr2;

	if (!dst && !src)
		return (NULL);
	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	while (n-- > 0)
		*(ptr1++) = *(ptr2++);
	return ((void *)dst);
}

static void print_with_env(char *str)
{
	int i;
	int len;
	int start;
	int end;
	char *var_name;
	char *env_value;

	if (!str)
		return;

	len = strlen(str);
	if (len == 0)
		return;

	i = 0;
	while (i < len)
	{
		if (str[i] == '$' && i + 1 < len)
		{
			start = i + 1;
			end = start;
			while (end < len && (str[end] == '_' ||
								 (str[end] >= 'A' && str[end] <= 'Z') ||
								 (str[end] >= 'a' && str[end] <= 'z') ||
								 (str[end] >= '0' && str[end] <= '9')))
			{
				end++;
			}
			if (end > start)
			{
				int var_len = end - start;
				var_name = (char *)malloc(sizeof(char) * (var_len + 1));
				if (var_name)
				{
					ft_memcpy(var_name, str + start, var_len);
					var_name[var_len] = '\0';
					env_value = getenv(var_name);
					if (env_value)
						printf("%s", env_value);
					free(var_name);
					i = end;
					continue;
				}
			}
		}
		printf("%c", str[i]);
		i++;
	}
}

int builtin_echo(char **args)
{
	int i;
	int option_n;

	if (!args[1])
	{
		printf("\n");
		return (0);
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
			print_with_env(args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!option_n)
		printf("\n");
	return (0);
}
