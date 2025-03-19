/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/03/19 15:30:21 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	parse_exe(char *input, t_mini *mini)
{

	mini->cmd = parsecmd(input);
	runcmd(mini->cmd, STDIN_FILENO, STDOUT_FILENO, mini);
	freecmd(mini->cmd);
	free(mini->cmd);
}

void	start_shell(char **envp)
{
	char	*input;
	t_mini	*mini;

	input = NULL;
	mini = malloc(sizeof(*mini));
	ft_memset(mini, 0, sizeof(*mini));
	mini->env = env_cloner(envp);
	printf("%s", IMG);
	while (1)
	{
		input = readline("minipierpaolo> ");
		if (!input)
		{
			printf("Pierpaolo dismissed you...\n");
			mtxs_free(mini->env);
			free(mini);
			rl_clear_history();
			break ;
		}
		if (*input)
		{
			add_history(input);
			parse_exe(input, mini);
		}
		free(input);
	}
}

int	main(int ac, char **av, char **envp)
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
