/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:19:27 by msisto            #+#    #+#             */
/*   Updated: 2025/05/17 16:44:00 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eof_checker(char *line, char *rule)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	if (ft_strlen_g(line) != ft_strlen_g(rule))
		return (0);
	while (line[i])
	{
		if (line[i] != rule[i])
			return (0);
		i++;
	}
	return (1);
}

static void	hd_write(char *line, int fd)
{
	write(fd, line, ft_strlen_g(line));
	write(fd, "\n", 1);
	free(line);
}

void	here_doc(t_redircmd *rcmd, char *rule, t_mini *mini)
{
	char	*line;
	int		fd;

	fd = open(rcmd->file, rcmd->mode, 0777);
	if (fd == -1)
		panic_fun("minipierpaolo: ", "unable to open heredoc\n", 1, 0);
	while (1)
	{
		line = readline("> ");
		if (g_exit_code != 0 || eof_checker(line, rule) == 1)
			break ;
		hd_write(line, fd);
	}
	free_mini(mini);
	close(fd);
}

void	handle_heredoc(t_redircmd *rcmd, char *rule, t_mini *mini)
{
	pid_t	pid;
	int		status;

	signal_set(0);
	pid = fork();
	if (pid == -1)
		panic_fun("minipierpaolo: ", "fork failed\n", 1, 0);
	if (pid == 0)
	{
		signal_set(1);
		here_doc(rcmd, rule, mini);
		exit(g_exit_code);
	}
	else
	{
		waitpid(pid, &status, 0);
		signal_set(2);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		{
			unlink(rcmd->file);
			free_mini(mini);
			exit(WEXITSTATUS(status));
		}
	}
}

void	runredir(t_cmd *cmd, t_mini *mini)
{
	t_redircmd	*rcmd;
	char		*name;
	int			fd;

	rcmd = (t_redircmd *)cmd;
	if (rcmd->here_doc == 0)
	{
		name = var_content_elab(rcmd->file, mini->env);
		if (rcmd->mode == O_RDONLY)
			close(0);
		else if (rcmd->mode > O_RDONLY)
			close(1);
		if (open(name, rcmd->mode, 0777) == -1)
			panic_fun("minipierpaolo: ", name, 1, 0);
		free(name);
	}
	else
	{
		close(0);
		fd = open(rcmd->here_doc_name, O_RDONLY);
		if (fd == -1)
			panic_fun("minipierpaolo: ", "heredoc reopen failed\n", 1, 0);
		unlink(rcmd->here_doc_name);
	}
	runcmd(rcmd->cmd, mini);
}
