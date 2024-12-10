/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:24 by efoschi           #+#    #+#             */
/*   Updated: 2024/12/10 14:40:43 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//eseguire il comando EXEC
void	execcmd(t_execcmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (cmd->argv[0] == NULL)
		exit(0);
	if (pid == 0)
	{
		execvp(cmd->argv[0], cmd->argv);
		perror("execvp");
		exit(1);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, NULL, 0);
	}
}

//eseguire il comando REDIR
void	redircmd(t_redircmd *cmd)
{
	int	fd;

	fd = open(cmd->file, cmd->mode, 0644);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	dup2(fd, cmd->fd);
	close(fd);
	execute((t_cmd *)cmd->cmd);
}

//eseguire il comando PIPE
void	pipecmd(t_pipecmd *cmd)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execute((t_cmd *)cmd->left);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execute((t_cmd *)cmd->right);
	}
}

//eseguire il comando LIST
void	listcmd(t_listcmd *cmd)
{
	execute((t_cmd *)cmd->left);
	execute((t_cmd *)cmd->right);
}

//eseguire il comando BACK
void	backcmd(t_backcmd *cmd)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		execute((t_cmd *)cmd->cmd);
		exit(0);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
}
