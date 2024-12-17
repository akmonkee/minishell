/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2024/12/17 16:54:27 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_shell(char **envp)
{
	char	*input;
	char	*fr;

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
			fr = input;
			add_history(input);
			// if (strcmp(input, "run_tests") == 0) // Controllo per run_tests
			// {
			// 	run_tests(); // Esegui tutti i test
			// }
			// else
			// {
			// 	printf("Unknown command: %s\n", input);
			// }
			input = fr;
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
	if (isatty(STDIN_FILENO))
		start_shell(envp);
	else
	{
		write(2, "Error: Not running in a terminal.\n", 34);
		exit(EXIT_FAILURE);
	}


	return (0);
}
