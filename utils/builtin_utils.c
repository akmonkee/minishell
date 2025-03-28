/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:54:19 by msisto            #+#    #+#             */
/*   Updated: 2025/02/11 11:54:19 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_words(char *s, char c)
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

void	strjoin_alloc(char **ps, char **mtx, int j, char c)
{
	char	*s;

	s = *ps;
	mtx[j] = var_ex(s, c);
	if (!mtx[j])
	{
		mtxs_free(mtx);
		return ;
	}
	while (*s != '\0' && *s != c)
		s++;
	*ps = s;
}

char	**ft_split_bt(char *s, char c)
{
	char **matrix;
	int j;
	int word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	matrix = malloc(sizeof(char *) * (word_count + 1));
	if (!matrix)
		return (NULL);
	j = 0;
	while (*s != '\0' && j < word_count)
	{
		while (*s != '\0' && *s == c)
			s++;
		if (*s != '\0')
		{
			strjoin_alloc(&s, matrix, j, c);
			j++;
		}
	}
	if (matrix)
		matrix[j] = NULL;
	return (matrix);
}

void	exe_bt(char **input, t_mini *mini)
{
	char	**tmp;

	tmp = NULL;
	if (!input)
		return ;
	if (fullcmp(input[0], "exit") == 0)
		builtin_exit(input);
	else if (fullcmp(input[0], "cd") == 0)
		tmp = (char **)builtin_cd(input[1], mini->env);
	else if (fullcmp(input[0], "export") == 0)
		tmp = (char **)builtin_export(input, mini->env);
	else if (fullcmp(input[0], "unset") == 0)
		builtin_unset(input, mini);
	else if (fullcmp(input[0], "pwd") == 0)
	{
		if (input[1] != NULL)
			g_exit_code = 2;
		else
			builtin_pwd(mini->env);
	}
	else if (fullcmp(input[0], "env") == 0)
	{
		if (input[1] != NULL)
			g_exit_code = 2;
		else
			builtin_env(mini->env);
	}
	else if (fullcmp(input[0], "echo") == 0)
		builtin_echo(input, mini->env);
	else
		tmp = NULL;
	if (tmp)
	{
		mtxs_free(mini->env);
		mini->env = env_cloner(tmp);
		mtxs_free(tmp);
	}
}

int	control_bt(char *input)
{
	int		ret;

	ret = 0;
	if (!input)
		return (1);
	if (fullcmp(input, "cd") == 0)
		ret = 1;
	else if (fullcmp(input, "exit") == 0)
		ret = 1;
	else if (fullcmp(input, "export") == 0)
		ret = 1;
	else if (fullcmp(input, "unset") == 0)
		ret = 1;
	else if (fullcmp(input, "pwd") == 0)
		ret = 1;
	else if (fullcmp(input, "env") == 0)
		ret = 1;
	else if (fullcmp(input, "echo") == 0)
		ret = 1;
	return (ret);
}
