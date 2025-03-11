/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:58:55 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:58:55 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	**builtin_cd(char *input, char **env)
{
	char	**split;
	char	*curr_pwd;
	char	**path_s;
	char	*path;
	int		i;
	int		k;
	int		len;

	i = 0;
	curr_pwd = find_n_ret("PWD", env);
	printf("%s\n", curr_pwd);
	input+=2;
	while (*input == ' ' && *input != '\0')
		input++;
	split = ft_split_bt(input, '/');
	path_s = ft_split_bt(curr_pwd, '\0');
	path = var_ex(path_s[i], '\0');
	while (path_s[++i] != NULL)
	{
		path = ft_strjoinf1(path, "/");
		path = ft_strjoinf1(path, path_s[i]);
	}
	mtxs_free(path_s);
	i = -1;
	while (split[++i] != NULL)
	{
		k = 0;
		if (varcmp(split[i], "..", ft_strlen_g(split[i])) == 1)
		{
			path_s = ft_split_bt(path, '/');
			free(path);
			len = mtx_len(path_s);
			path = var_ex(path_s[k], '\0');
			while (++k < len - 1)
			{
				path = ft_strjoinf1(path, "/");
				path = ft_strjoinf1(path, path_s[k]);
			}
			mtxs_free(path_s);
		}
		else
		{
			path = ft_strjoinf1(path, "/");
			path = ft_strjoinf1(path, split[i]);
		}
	}
	mtxs_free(split);
	chdir(input);
	curr_pwd = ft_strjoinf2("OLD_PWD=", curr_pwd);
	free(curr_pwd);
	path = ft_strjoinf2("/", path);
	printf("%s\n", path);
	if (chdir(path) == -1)
	{
		printf("cd: %s: No such file or directory\n", path);
		free(path);
		return (NULL);
	}
	free(path);
	return (NULL);
}
