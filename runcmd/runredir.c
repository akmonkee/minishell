/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runredir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:19:27 by msisto            #+#    #+#             */
/*   Updated: 2025/01/15 13:56:49 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc(char *rule)
{
	char	*line;
	int		fd;

	fd = open("temp_file", O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (fd == -1)
		ft_custom_error(5);
	line = get_next_line(0, 1);
	while (line != NULL && ft_strnstr(line, rule, ft_strlen(rule)) == 0)
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_next_line(0, 1);
	}
	get_next_line(0, 0);
	free(line);
	close(fd);
	fd = open("temp_file", O_RDONLY);
	if (fd == -1)
		ft_custom_error(2);
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
	else if (rcmd->mode > O_RDONLY)
		close(1);
	if (open(rcmd->file, rcmd->mode, 0777) < 0)
	{
		write (2, "Error\n open failed\n", 19);
		return ;
	}
	runcmd(rcmd->cmd, envp);
}
