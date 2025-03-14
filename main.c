/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/03/14 17:53:51 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	parse_exe(char *input, char **envp)
{
	t_cmd	*cmd;
	pid_t	pid;
	int		exit_status;

	cmd = parsecmd(input);
	signal(SIGQUIT, ign);
	signal(SIGINT, ign);
	signal(SIGTERM, ign);
	pid = fork();
	if (pid == -1)
	{
		perror("failed to fork \n");
		g_exit_code = 1;
		freecmd(cmd);
		free(cmd);
	}
	else if (pid == 0)
	{
		doc_cmd(cmd, envp);
		runcmd(cmd, envp);
		freecmd(cmd);
		free(cmd);
		free(input);
		mtxs_free(envp);
		exit (g_exit_code);
	}
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
		freecmd(cmd);
		free(cmd);
	}
}

void	start_shell(char **envp)
{
	char	**tmp;
	char	**env;
	char	*input;

	input = NULL;
	env = env_cloner(envp);
	printf("%s", IMG);
	while (1)
	{
		input = readline("minipierpaolo> ");
		if (!input)
		{
			printf("Pierpaolo dismissed you...\n");
			mtxs_free(env);
			rl_clear_history();
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (control_bt(input, env) == 1)
			{
				tmp = (char **)exe_bt(input, env);
				if (tmp)
				{
					mtxs_free(env);
					env = env_cloner(tmp);
					mtxs_free (tmp);
				}
			}
			else
				parse_exe(input, env);
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
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler);
	if (isatty(STDIN_FILENO))
		start_shell(envp);
	else
	{
		write(2, "Error: Not running in a terminal.\n", 34);
		exit(EXIT_FAILURE);
	}
	return (0);
}
