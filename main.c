/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/02/04 11:54:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_exe(char *input, char **envp)
{
	t_cmd	*cmd;

	cmd = parsecmd(input);
	runcmd(cmd, envp);
	freecmd(cmd);
	free(cmd);
	free(input);
}

// void	start_shell(char **envp)
// {
// 	char	*input;
// 	pid_t	pid;

// 	input = NULL;
// 	printf("%s", IMG);
// 	while (1)
// 	{
// 		input = readline("minipierpaolo> ");
// 		if (!input)
// 		{
// 			printf("Pierpaolo dismissed you...\n");
// 			rl_clear_history();
// 			break ;
// 		}
// 		if (*input)
// 		{
// 			add_history(input);
// 			pid = fork();
// 			if (pid == -1)
// 			{
// 				write(2, "fork non riuscito\n", 18);
// 				return ;
// 			}
// 			if (pid == 0)
// 				return (parse_exe(input, envp));
// 			else
// 				wait(NULL);
// 		}
// 		free(input);
// 	}
// }

void start_shell(char **envp)
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
			break;
		}
		if (*input)
		{
			add_history(input);
			cmd = parsecmd(input);
			if (cmd->type == EXEC)
			{
				t_execcmd *ecmd = (t_execcmd *)cmd;
				if (ecmd->argv[0] && is_builtin(ecmd->argv[0]))
				{
					control_bt(ecmd->argv[0], cmd);
					freecmd(cmd);
					free(cmd);
					free(input);
					continue;
				}
			}
			pid = fork();
			if (pid == -1)
			{
				write(2, "fork non riuscito\n", 18);
				return;
			}
			if (pid == 0)
				parse_exe(input, envp);
			else
			{
				wait(NULL);
				freecmd(cmd);
				free(cmd);
			}
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
	signal(SIGQUIT, handle_sigquit);
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
