/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 10:24:30 by msisto            #+#    #+#             */
/*   Updated: 2024/11/20 10:36:07 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_ex(char	**envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(STDOUT_FILENO, "declare -x ", 11);
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}

void	cd_ex(char	**envp)
{
	int	i;
	int	status;
	char	*home;

	i = 0;
	status = 0;
	while (envp[i])
	{
		if (ft_strcmp(envp[i], "HOME=") == 0)
		{
			home = home_set(envp[i]);
			break ;
		}
		i++;
	}
	if (!home)
	{
		perror("HOME not set\n");
		return ;
	}
	status = chdir(home);
	if (status != 0)
		perror("cd");
	free(home);
}

void	env_ex(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(STDOUT_FILENO, envp[i], ft_strlen(envp[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}


void	pwd_ex()
{
	char cwd[1024];
	char *result;

	result = getcwd(cwd, sizeof(cwd));
	if (result != NULL)
	{
		write(STDOUT_FILENO, result, ft_strlen(result));
		write(STDOUT_FILENO, "\n", 1);
	}
	else
		perror("pwd");
}

int	builtin_check(char *input, char **envp)
{
	if (ft_strcmp(input, "cd") == 0)
		return (cd_ex(envp), 0);
	else if(ft_strcmp(input, "exit") == 0)
	{
		return (0);
	}
	else if(ft_strcmp(input, "pwd") == 0)
		return (pwd_ex(), 0);
	else if(ft_strcmp(input, "export") == 0)
		return (export_ex(envp), 0);
	else if(ft_strcmp(input, "unset") == 0)
	{
		return (0);
	}
	else if(ft_strcmp(input, "env") == 0)
		return (env_ex(envp), 0);
	else
		return (1);
}
