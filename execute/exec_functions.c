/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:18:24 by efoschi           #+#    #+#             */
/*   Updated: 2025/01/17 11:31:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_op(t_main *main, t_cmd *cur)
{
	char	**arg;
	char	*str;

	signal(SIGQUIT, sigbs);
	if (control_bt(main, cur) == 0)
	{
		if (cur->cmd[0] == ' ' && cur->cmd[1] == '\0')
			exit(write(2, "Minishell: error occured while executing command\n", 50) + 84);
		str = /*program_name(cur-cmd, get_env(main, "PATH"));*/
		arg = take_args(main, cur, cur->cmd);
		g_code_exit = 269;
		if (str != NULL)
		{
			if (ft_strncmp(str, "o red", 5) == 0 && free_matrix(arg) == 0)
				exit(0);
			execve(str, arg, main->env);
			free(str);
		}
		free_matrix(arg);
		g_code_exit = 127;
		exit(write(2, "Minishell: command not found\n", 29) + 84);
	}
	else
		exit(super_free(main));
}

void	sigbs(int sig)
{
	(void)sig;
	write(0, "Minipierpaolo: Close 0 input\n", 29);
	write(0, "Minipierpaolo: Close 0 input\n", 29);
	write(0, "Minipierpaolo: Close 0 input\n", 29);
	exit(131);
}
