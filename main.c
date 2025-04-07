/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/04/07 09:44:15 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

void	panic_fun(char *pre, char *input, int e_code, int exit_flag)
{
	char	*c_msg;

	c_msg = ft_strjoin(pre, input);
	perror(c_msg);
	free(c_msg);
	g_exit_code = e_code;
	if (exit_flag == 1)
		exit(g_exit_code);
}

static void	pexe_ll(t_mini *mini)
{
	pid_t		pid;
	int			exit_status;

	signal(SIGQUIT, ign);
	signal(SIGINT, ign);
	signal(SIGTERM, ign);
	pid = fork();
	if (pid == 0)
	{
		runcmd(mini->cmd, mini);
		exit(0);
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
	}
}

void	parse_exe(char *input, t_mini *mini)
{
	t_execcmd	*ecmd;

	mini->cmd = parsecmd(input);
	if (!mini->cmd)
		return ;
	ecmd = (t_execcmd *)mini->cmd;
	if (mini->cmd && mini->cmd->type == EXEC && control_bt(ecmd->argv[0]))
		runcmd(mini->cmd, mini);
	else if (mini->cmd)
		pexe_ll(mini);
	freecmd(mini->cmd);
	free(mini->cmd);
}

void	start_shell(char **envp)
{
	char	*input;
	t_mini	*mini;

	mini = malloc(sizeof(*mini));
	ft_memset(mini, 0, sizeof(*mini));
	mini->env = env_cloner(envp);
	print_pierpaolo();
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
