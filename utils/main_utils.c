/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efoschi <efoschi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:00:44 by efoschi           #+#    #+#             */
/*   Updated: 2025/03/11 17:00:44 by efoschi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fork_and_execute(char *input, char ***env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		write(2, "fork non riuscito\n", 18);
		return;
	}
	if (pid == 0)
		return (parse_exe(input, *env));
	else
		wait(NULL);
}

void	handle_input(char *input, char ***env)
{
	char	**tmp;
	pid_t	pid;

	if (*input)
	{
		add_history(input);
		if (control_bt(input, *env) == 1)
		{
			tmp = (char **)exe_bt(input, *env);
			if (tmp)
			{
				mtxs_free(*env);
				*env = env_cloner(tmp);
				mtxs_free(tmp);
			}
		}
		else
			fork_and_execute(input, env);
	}
	free(input);
}
