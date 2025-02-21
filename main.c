/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:57:54 by efoschi           #+#    #+#             */
/*   Updated: 2025/02/21 12:00:23 by msisto           ###   ########.fr       */
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
	pid_t	pid;

	input = NULL;
	printf("%s", IMG);
	while (1)
	{
		printf("in main %p\n", envp);
		input = readline("minipierpaolo> ");
		if (!input)
		{
			printf("Pierpaolo dismissed you...\n");
			mtxs_free(envp);
			rl_clear_history();
			break ;
		}
		if (*input)
		{
			add_history(input);
			if (control_bt(input, envp) == 1)
			{
				pid = fork();
				if (pid == -1)
				{
					write(2, "fork non riuscito\n", 18);
					return ;
				}
				if (pid == 0)
					return (parse_exe(input, envp));
				else
					wait(NULL);
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
		start_shell(env_cloner(envp));
	else
	{
		write(2, "Error: Not running in a terminal.\n", 34);
		exit(EXIT_FAILURE);
	}
	return (0);
}


