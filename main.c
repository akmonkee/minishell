/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:57:54 by efoschi           #+#    #+#             */
/*   Updated: 2025/03/11 17:07:23 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code = 0;

char	**env_cloner(char **envp)
{
	char	**ret;
	int		i;
	int		k;

	i = 0;
	while (envp[i] != NULL)
		i++;
	ret = malloc((i + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		k = 0;
		ret[i] = malloc(ft_strlen_g(envp[i]) + 1);
		while (k < ft_strlen_g(envp[i]))
		{
			ret[i][k] = envp[i][k];
			k++;
		}
		ret[i][k] = '\0';
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	parse_exe(char *input, char **envp)
{
	t_cmd	*cmd;

	cmd = parsecmd(input);
	//doc_cmd(cmd, envp);
	runcmd(cmd, envp);
	freecmd(cmd);
	free(cmd);
	free(input);
	mtxs_free(envp);
}

void	start_shell(char **envp)
{
	char	*input;
	char	**env;

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
		handle_input(input, &env);
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
