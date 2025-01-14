/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/01/14 13:07:27 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, "minipierpaolo> ", 15);
}

void	start_shell(char **envp)
{
	char	*input;
	pid_t	pid;
	t_cmd	*cmd;

	input = NULL;
	printf("%s", IMG);
	while (1)
	{
		input = readline("minipierpaolo> ");
		if (!input)
		{
			printf("Pierpaolo dismissed you...\n");
			rl_clear_history();
			break ;
		}
		if (*input)
		{
			add_history(input);
			cmd = NULL;
			pid = fork();
			if (pid == -1)
			{
				write(2, "fork non riuscito\n", 18);
				return ;
			}
			if (pid == 0)
			{
				cmd = parsecmd(input);
				runcmd(cmd, envp);
				freecmd(cmd);
				free(cmd);
				free(input);
				return ;
			}
			else
				wait(NULL);
		}
		free(input);
	}
}

int	main(int ac, char **av, char *envp[])
{
	if (ac > 1)
	{
		write(2, "Error\nno args allowed\n", 22);
		return (1);
	}
	signal(SIGINT, handle_sigint);
	if (isatty(STDIN_FILENO))
		start_shell(envp);
	else
	{
		write(2, "Error: Not running in a terminal.\n", 34);
		exit(EXIT_FAILURE);
	}
	return (0);
}
