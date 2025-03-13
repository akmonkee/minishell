/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:59:21 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/11 11:59:21 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*true_pwd_ex()
{
	int		i;
	char	buf[260];
	char	*ret;

	i = -1;
	getcwd(buf, 260);
	ret = malloc(ft_strlen_g(buf) + 1);
	if (!ret)
		return (NULL);
	while (buf[++i] != '\0')
		ret[i] = buf[i];
	ret[i] = '\0';
	return (ret);
}

void	builtin_pwd(char **envp)
{
	char	var[260];
	int		i;

	getcwd(var, 260);
	printf("%s\n", var);
}
