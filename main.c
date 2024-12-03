/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2024/12/03 15:16:37 by msisto           ###   ########.fr       */
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
			printf("%d\n", gettoken(&input, (input + ft_strlen(input)), 0, 0));
			input = fr;
		}
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
	return (0);
}
