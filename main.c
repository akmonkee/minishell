/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/01/21 16:30:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_code_exit = 0;

// void	start_shell(t_main *main, char **envp)
// {
// 	char	*input;
// 	char	*fr;

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
// 			fr = input;
// 			add_history(input);
// 			execute(&main, NULL, 0);
// 			input = fr;
// 		}
// 		free(input);
// 	}
// }

// int	main(int ac, char **av, char *envp[])
// {
// 	t_main	main;

// 	if (ac > 1)
// 	{
// 		write(2, "Error\nno args allowed\n", 22);
// 		return (1);
// 	}
// 	if (isatty(STDIN_FILENO))
// 		start_shell(&main, envp);
// 	else
// 	{
// 		write(2, "Error: Not running in a terminal.\n", 34);
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv, char **env)
{
	t_main	m;

	if (argc >= 2 || initialize_start(&m, env))
		return (write(2, "Panic: problem problem!\n", 25));
	// if (signal(SIGINT, sigc) == SIG_ERR || signal(SIGTERM, sigd) == SIG_ERR
	// 	|| signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	// 	return (printf("Marshal: Signal error"));
	(void)argv;
	while (1)
	{
		m.input = get_command_f_0();
		if (m.input == NULL)
		{
			rl_clear_history();
			return (free_matrix(m.env), 1);
		}
		if ((m.input[0] == ' ' || m.input[0] == '\0') && free_str(m.input))
			continue ;
		//split_cmd(&m);
		execute(&m, NULL, 0);
		free_all(&m);
	}
	rl_clear_history();
	return (free_matrix(m.env), 0);
}
