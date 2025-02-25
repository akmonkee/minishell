/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:21:33 by msisto            #+#    #+#             */
/*   Updated: 2025/02/25 14:51:55 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

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
	doc_cmd(cmd, envp);
	runcmd(cmd, envp);
	freecmd(cmd);
	free(cmd);
	free(input);
	mtxs_free(envp);
}

void	start_shell(char **envp)
{
	char	**tmp;
	char	**env;
	char	*input;
	pid_t	pid;

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
		if (*input)
		{
			add_history(input);
			if (control_bt(input, env) == 1)
			{
				tmp = (char **)exe_bt(input, env);
				if (tmp)
				{
					mtxs_free(env);
					env = env_cloner(tmp);
					mtxs_free (tmp);
				}
			}
			else
			{
				pid = fork();
				if (pid == -1)
				{
					write(2, "fork non riuscito\n", 18);
					return ;
				}
				if (pid == 0)
					return (parse_exe(input, env));
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
		start_shell(envp);
	else
	{
		write(2, "Error: Not running in a terminal.\n", 34);
		exit(EXIT_FAILURE);
	}
	return (0);
}
