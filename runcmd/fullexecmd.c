/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullexecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:35:28 by msisto            #+#    #+#             */
/*   Updated: 2024/12/20 14:15:59 by msisto           ###   ########.fr       */
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
	if (!mtx)
		return ;
	else
	{
		while (mtx[++i] != NULL)
		{
			free(mtx[i]);
			mtx[i] = NULL;
		}
		free(mtx);
		mtx = NULL;
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
	//char	**diff_path;
	char	*exe_path;

	path = path_finder(envp);
	if (!path)
	{
		write(2, "unable to create path\n", 22);
		return ;
	}
	//diff_path = ft_split(command, ' ', 0, 0);
	//if (!diff_path)
	//	mtxs_free(path);
	//exe_path = cmd_check(path, diff_path[0]);
	exe_path = cmd_check(path, command[0]);
	if (!exe_path)
		return ;
	else
	{
		execve(exe_path, command, envp);
		mtxs_free(path);
	}
}
