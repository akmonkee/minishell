/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullexecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:35:28 by msisto            #+#    #+#             */
/*   Updated: 2025/03/19 15:34:33 by msisto           ###   ########.fr       */
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

void	ffree(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = '\0';
		i++;
	}
	free(str);
}

void	mtxs_free(char **mtx)
{
	int	i;

	i = 0;
	if (!mtx)
		return ;
	while (mtx[i])
	{
		ffree(mtx[i]);
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

void	execve_cmd(char **command, t_mini *mini)
{
	char	**path;
	char	*exe_path;

	if (mini->cmd->type == REDIR)
		runredir(mini->cmd, STDIN_FILENO, STDOUT_FILENO, mini);
	path = path_finder(mini->env);
	if (!path)
	{
		perror("unable to create path\n");
		exit (1);
	}
	exe_path = cmd_check(path, command[0]);
	mtxs_free(path);
	if (!exe_path)
		exit (1);
	if (execve(exe_path, command, mini->env) == -1)
		free(exe_path);
}

void	ft_execute_command(char **command, t_mini *mini)
{
	int	pid;
	int	exit_status;

	if (control_bt(command[0]) == 1)
		exe_bt(command, mini);
	else
	{
		signal(SIGQUIT, ign);
		signal(SIGINT, ign);
		signal(SIGTERM, ign);
		pid = fork();
		if (pid == 0)
			execve_cmd(command, mini);
		else
		{
			signal(SIGINT, signal_execve);
			signal(SIGQUIT, signal_execve);
			waitpid(pid, &exit_status, 0);
			signal(SIGINT, signal_handler);
			signal(SIGTERM, signal_handler);
			signal(SIGQUIT, ign);
			if (WIFEXITED(exit_status))
				g_exit_code = WEXITSTATUS(exit_status);
		}
	}
}
