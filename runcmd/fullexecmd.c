/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullexecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:35:28 by msisto            #+#    #+#             */
/*   Updated: 2025/01/07 10:49:00 by msisto           ###   ########.fr       */
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
	free(path);
	return (fcmd);
}

void	mtxs_free(char **mtx)
{
	int	i;

	i = -1;
	if (mtx == NULL)
		return ;
	else
	{
		while (mtx[++i] != NULL)
		{
			free(mtx[i]);
		}
		free(mtx);
	}
}

char	*cmd_check(char **path, char *command)
{
	int		i;
	char	*command_path;

	i = 0;
	while (path[i] != NULL)
	{
		command_path = ft_strjoin(ft_strjoin(path[i], "/"), command);
		if (access(command_path, X_OK) == 0)
			return (command_path);
		i++;
		free(command_path);
		command_path = NULL;
	}
	return (NULL);
}

void	ft_execute_command(char **command, char **envp)
{
	char	**path;
	char	*exe_path;
	pid_t	pid;

	path = path_finder(envp);
	if (!path)
	{
		write(2, "unable to create path\n", 22);
		return ;
	}
	exe_path = cmd_check(path, command[0]);
	if (!exe_path)
		return ;
	pid = fork();
	if (pid == -1)
	{
		mtxs_free(path);
		return ;
	}
	if (pid == 0)
	{
		if (execve(exe_path, command, envp) == -1)
			mtxs_free(path);
	}
	else
	{
		wait(NULL);
		if (path)
			printf("dio bastonato\n");
		free(exe_path);
	}
}
