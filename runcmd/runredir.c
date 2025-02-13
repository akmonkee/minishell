/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:19:27 by msisto            #+#    #+#             */
/*   Updated: 2025/02/13 11:10:56 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eof_checker(char *line, char *rule)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i] != '\0' || line[i] != '\n' || rule[i] != '\0')
	{
		if (line[i] != rule[i])
			return (0);
		i++;
	}
	if ((line[i] == '\n'|| line[i] == '\0') && rule[i] == '\0')
		return (1);
	return (0);
}

void	here_doc(t_redircmd *rcmd, char *rule)
{
	char	*line;
	int		fd;

	fd = open("temp_file", rcmd->mode, 0777);
	if (fd == -1)
	write(2, "Error\nfailed to create temp file\n", 33);
	while (1)
	{
		line = readline("> ");
		if (eof_checker(line, rule) == 1 || !line)
			break ;
		if (line)
		{
			write(fd, line, ft_strlen_g(line));
			free(line);
		}
	}
	free(line);
	close(fd);
	fd = open("temp_file", O_RDONLY);
	if (fd == -1)
		write(2, "Error\nfailed to open temp file\n", 31);
	dup2(fd, STDIN_FILENO);
	close(fd);
	if (access("temp_file", R_OK) == 0)
		unlink("temp_file");
}

void	runredir(t_cmd *cmd, char **envp)
{
	t_redircmd	*rcmd;

	rcmd = (t_redircmd *)cmd;
	if (rcmd->mode == O_RDONLY)
		close(0);
	if (rcmd->mode > O_RDONLY && rcmd->here_doc == 0)
		close(1);
	if (rcmd->here_doc == 1)
	{
		here_doc(rcmd, rcmd->file);
	}
	else
		open(rcmd->file, rcmd->mode, 0777);
	runcmd(rcmd->cmd, envp);
}
