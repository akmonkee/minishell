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

void	**pwd_mod(char *str, char **env)
{
	int		i;
	char	*var_name;
	char	*ex_env;
	char	**ret;

	i = -1;
	var_name = var_ex(str, '=');
	while (env[++i] != NULL)
	{
		ex_env = var_ex(env[i], '=');
		if (varcmp(var_name, ex_env, ft_strlen_g(var_name)) == 1)
		{
			free(ex_env);
			free(var_name);
			free(env[i]);
			env[i] = var_ex(str, '\0');
			return ((void **)env);
		}
		free(ex_env);
	}
	free(var_name);
	i = mtx_len(env);
	ret = (char **)ft_realloc(env, i + 1);
	ret[i] = var_ex(str, '\0');
	return ((void **) ret);
}

char	*true_pwd_ex(void)
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
