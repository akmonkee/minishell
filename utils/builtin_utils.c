/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:47 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:47 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_substr(const char *s, unsigned int start, size_t len)
{
	char *substr;
	size_t i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_g(s))
	{
		substr = malloc(1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	substr = malloc(len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (count);
}

char **ft_split_bt(char const *s, char c)
{
	char **matrix;
	int i;
	int j;
	int k;
	int word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	matrix = malloc(sizeof(char *) * (word_count + 1));
	if (!matrix)
		return (NULL);
	i = 0;
	j = 0;
	while (j <= word_count)
		matrix[j++] = NULL;
	j = 0;
	while (s[i] && j < word_count)
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
		{
			k = i;
			while (s[i] && s[i] != c)
				i++;

			matrix[j] = ft_substr(s, k, i - k);
			if (!matrix[j])
			{
				while (j > 0)
					free(matrix[--j]);
				free(matrix);
				return (NULL);
			}
			j++;
		}
	}
	matrix[j] = NULL;
	return (matrix);
}

/*void	**exe_bt(char *input, char **env)
{
	char **args;

	if (!input)
		ret = 1;
	args = ft_split_bt(input, ' ');
	if (!args)
		ret = 1;
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		ret = builtin_pwd(env);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		ret = builtin_cd(input, env);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ret = builtin_echo(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ret = builtin_env(env, 0);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ret = builtin_exit(input);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ret = builtin_export(input, env);
	// else if (ft_strncmp(args[0], "unset", 5) == 0)
	// {
	// 	if (args[1])
	// 		ret = builtin_unset(env, args[1]);
	// 	else
	// 		ret = 1;
	// }
	else
		ret = 1;
	mtxs_free(args);
	return (ret);
}*/

int	control_bt(char *input, char **env)
{
	char	**args;
	int		ret;

	ret = 0;
	if (!input)
		return (1);
	args = ft_split_bt(input, ' ');
	if (!args)
		return (1);
	if (ft_strncmp(args[0], "pwd", 3) == 0)
		ret = 1;
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		ret = 1;
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		ret = 1;
	else if (ft_strncmp(args[0], "env", 3) == 0)
		ret = 1;
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		ret = 1;
	else if (ft_strncmp(args[0], "export", 6) == 0)
		ret = 1;
	// else if (ft_strncmp(args[0], "unset", 5) == 0)
	// {
	// 	if (args[1])
	// 		ret =args[1]);
	// 	else
	// 		ret =(args);
	mtxs_free(args);
	return (ret);
}

