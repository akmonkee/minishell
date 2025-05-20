/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/05/20 17:25:46 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	panic_fun(char *pre, char *input, int e_code, int exit_flag)
{
	char	*c_msg;

	if (!input)
		perror(pre);
	else
	{
		if (exit_flag == 1)
			c_msg = ft_strjoinf1(pre, input);
		else
			c_msg = ft_strjoin(pre, input);
		perror(c_msg);
		free(c_msg);
	}
	g_exit_code = e_code;
	if (exit_flag == 1)
		exit(g_exit_code);
}

static void	mini_str_set(t_mini *mini, int flag)
{
	if (flag == 1 || flag == 4)
		mini->env = NULL;
	if (flag == 2 || flag == 4)
		mini->input = NULL;
	if (flag == 3 || flag == 4)
		mini->cmd = NULL;
}

static void	ctrl_d_exit(t_mini *mini)
{
	printf("Pierpaolo dismissed you...\n");
	mtxs_free(mini->env);
	free(mini);
	rl_clear_history();
}

void	start_shell(char **envp)
{
	char	*input;
	t_mini	*mini;

	mini = malloc(sizeof(*mini));
	mini_str_set(mini, 4);
	mini->env = env_cloner(envp, 1);
	print_pierpaolo();
	while (1)
	{
		input = readline("minipierpaolo> ");
		if (!input)
		{
			ctrl_d_exit(mini);
			break ;
		}
		if (*input)
		{
			mini->input = input;
			add_history(input);
			parse_exe(input, mini);
		}
		free(input);
		mini_str_set(mini, 2);
	}
}

int	main(int ac, char **av, char **envp)
{
	if (ac > 1)
	{
		write(2, "Error\nno args allowed\n", 22);
		return (1);
	}
	signal(SIGQUIT, SIG_IGN);
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
