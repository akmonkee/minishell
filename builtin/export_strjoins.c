/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_strjoins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:08:10 by msisto            #+#    #+#             */
/*   Updated: 2025/03/11 15:31:40 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
