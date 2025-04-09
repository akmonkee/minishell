/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_strjoins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:10 by msisto            #+#    #+#             */
/*   Updated: 2025/04/09 13:39:15 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *path, char *cmd)
{
	int		i;
	int		c;
	char	*fcmd;

	if (!cmd)
		return (NULL);
	fcmd = malloc(ft_strlen(path) + ft_strlen(cmd) + 1);
	if (!fcmd)
		return (NULL);
	i = 0;
	c = 0;
	while (path[i])
		fcmd[c++] = path[i++];
	i = 0;
	while (cmd[i])
		fcmd[c++] = cmd[i++];
	fcmd[c] = '\0';
	return (fcmd);
}

char	*ft_strjoinf1(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*ret;

	if (!s2)
		return (NULL);
	ret = malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	c = 0;
	while (s1[i])
		ret[c++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[c++] = s2[i++];
	ret[c] = '\0';
	free(s1);
	return (ret);
}

char	*ft_strjoinf2(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*ret;

	if (!s2)
		return (NULL);
	ret = malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	c = 0;
	while (s1[i])
		ret[c++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[c++] = s2[i++];
	ret[c] = '\0';
	free(s2);
	return (ret);
}

char	*ft_strjoinf12(char *s1, char *s2)
{
	int		i;
	int		c;
	char	*ret;

	if (!s2)
		return (NULL);
	ret = malloc(ft_strlen_g(s1) + ft_strlen_g(s2) + 1);
	if (!ret)
		return (NULL);
	i = 0;
	c = 0;
	while (s1[i])
		ret[c++] = s1[i++];
	i = 0;
	while (s2[i])
		ret[c++] = s2[i++];
	ret[c] = '\0';
	free(s1);
	free(s2);
	return (ret);
}

char	*strjoin_path(char *path, int flag)
{
	int		i;
	int		len;
	char	*ret;
	char	**path_s;

	i = 0;
	path_s = ft_split_bt(path, '/');
	len = mtx_len(path_s);
	if (flag == 1)
	{
		free(path);
		len--;
	}
	ret = var_ex(path_s[i], '\0');
	while (++i < len)
	{
		ret = ft_strjoinf1(ret, "/");
		ret = ft_strjoinf1(ret, path_s[i]);
	}
	mtxs_free(path_s);
	return (ret);
}
