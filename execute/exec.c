/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 15:06:29 by efoschi           #+#    #+#             */
/*   Updated: 2025/01/21 15:55:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_pipe(t_main *main, t_cmd *cur, pid_t pid)
{
	int		fd[2];

	//check_pipe_fork(main, cur, fd, &pid);
	if (pid == 0)
	{
		close(fd[0]);
		child_op(main, cur);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
	}
}

static void	child(t_main *main, t_cmd *cur)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return ;
	if (pid == 0)
		child_op(main, cur);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_code_exit = WEXITSTATUS(status);
	}
}


static void	exec_bt(t_main *main, t_cmd *cur, char *str)
{
	main->print = 0;
	if (ft_strncmp(str, "export", 7) == 0)
		builtin_export(main, cur, (t_data2){0, extract_token(cur, 0, 0), 0, -1});
	if (ft_strncmp(str, "unset", 6) == 0)
		builtin_unset(main, cur, -1, extract_token(cur, 0, 0));
	if (ft_strncmp(str, "cd", 3) == 0)
		builtin_cd(main, cur, pick_env(main, "HOME"), take_args(main, cur, cur->cmd));
	main->print = 1;
	free(str);
}

static int	pipe_cmd(t_main *main, t_cmd *cur)
{
	exec_bt(main, cur, no_space(cur->cmd));
	if (!(cur->or == 1 && g_code_exit == 0))
	{
		child_pipe(main, cur, 0);
	}
	return (0);
}

//devo gestire l'execute dei vari comandi della shell
void	execute(t_main *main, char *str, int i)
{
	t_cmd	*cur;

	cur = main->lcmd;
	str = no_space(cur->cmd);
	if (main->ncmd == 1 && ft_strncmp(str, "exit", 5) == 0 && free_str(str))
		builtin_exit(main, cur->cmd, go_next(0, cur->cmd), 0);
	free(str);
	while (main->npipe == 0 && main->ncmd != i++)
	{
		exec_bt (main, cur, no_space(cur->cmd));
		if (!(cur->or == 1 && g_code_exit == 0))
			child(main, cur);
		cur = cur->next;
		dup2(main->in, 0);
		dup2(main->out, 1);
	}
	while (main->npipe != 0 && main->ncmd != i++ /*&& pipe_cmd(main, cur) == 0*/)
		cur = cur->next;
	while (waitpid(-1, &i, 0) > 0)
		;
	dup2(main->in, 0);
	dup2(main->out, 1);
}
