/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2024/11/28 14:56:03 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	start_shell(char **envp)
{
	char	*input;

	input = NULL;
	printf("%s", img);
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("Exiting shell...\n");
			rl_clear_history();
			break;
		}
		if (*input)
			add_history(input);
		free(input);
	}
}

int	main(int argc, char **argv, char *envp[])
{
	if (isatty(STDIN_FILENO))
		start_shell(envp);
	else
	{
		perror("Error: Not running in a terminal.\n");
		exit(EXIT_FAILURE);
	}
	return 0;
}
