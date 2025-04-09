/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:19:27 by msisto            #+#    #+#             */
/*   Updated: 2025/04/09 16:58:04 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eof_checker(char *line, char *rule)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] != '\0' || rule[i] != '\0')
	{
		if (line[i] != rule[i])
			return (0);
		i++;
	}
	if (line[i] == '\0' && rule[i] == '\0')
		return (1);
	return (0);
}

static void	hd_write(char *line, int fd)
{
	write(fd, line, ft_strlen_g(line));
	write(fd, "\n", 1);
	free(line);
}

void	here_doc(t_redircmd *rcmd, char *rule)
{
	char	*line;
	int		fd;

	fd = open("temp", rcmd->mode, 0777);
	if (fd == -1)
		panic_fun("minipierpaolo: ", "unable to open heredoc\n", 1, 0);
	while (1)
	{
		line = readline("> ");
		if (eof_checker(line, rule) == 1)
			break ;
		if (line)
			hd_write(line, fd);
	}
	free(line);
	close(fd);
	fd = open("temp", O_RDONLY);
	if (fd == -1)
		panic_fun("minipierpaolo: ", "unable to open heredoc\n", 1, 0);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (access("temp", R_OK) == 0)
		unlink("temp");
}

void	runredir(t_cmd *cmd, t_mini *mini)
{
	t_redircmd	*rcmd;
	char		*name;

	rcmd = (t_redircmd *)cmd;
	name = var_content_elab(rcmd->file, mini->env);
	if (rcmd->here_doc == 0)
	{
		if (rcmd->mode == O_RDONLY)
			close(0);
		else if (rcmd->mode > O_RDONLY)
			close(1);
		if (open(name, rcmd->mode, 0777) == -1)
			panic_fun("minipierpaolo: ", name, 1, 0);
	}
	else
		here_doc(rcmd, name);
	free(name);
	runcmd(rcmd->cmd, mini);
}
