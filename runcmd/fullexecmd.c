/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullexecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:35:28 by msisto            #+#    #+#             */
/*   Updated: 2025/02/13 13:56:27 by msisto           ###   ########.fr       */
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

void	mtxs_free(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		free(mtx[i]);
		i++;
	}
	free(mtx);
}

char	*cmd_check(char **path, char *command)
{
	int		i;
	char	*command_slash;
	char	*command_path;

	i = 0;
	while (path[i] != NULL)
	{
		command_slash = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(command_slash, command);
		if (access(command_path, X_OK) == 0)
		{
			free(command_slash);
			return (command_path);
		}
		i++;
		free(command_slash);
		free(command_path);
		command_slash = NULL;
		command_path = NULL;
	}
	return (NULL);
}

void	ft_execute_command(char **command, char **envp)
{
	char	**path;
	char	*exe_path;

	path = path_finder(envp);
	if (!path)
	{
		write(2, "unable to create path\n", 22);
		return ;
	}
	exe_path = cmd_check(path, command[0]);
	mtxs_free(path);
	if (!exe_path)
		return ;
	if (execve(exe_path, command, envp) == -1)
		free(exe_path);
}
