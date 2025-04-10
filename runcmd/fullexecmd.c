/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fullexecmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:35:28 by msisto            #+#    #+#             */
/*   Updated: 2025/04/10 13:20:19 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*cmd_check(char **path, char *command)
{
	int		i;
	char	*command_slash;
	char	*command_path;

	i = 0;
	while (path[i] != NULL)
	{
		command_slash = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(command_slash, command);
		if (access(command_path, X_OK) == 0)
		{
			free(command_slash);
			return (command_path);
		}
		i++;
		free(command_slash);
		free(command_path);
		command_slash = NULL;
		command_path = NULL;
	}
	return (NULL);
}

char	**command_elab(char **command, t_mini *mini)
{
	char	**ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(char *) * (mtx_len(command) + 1));
	while (i < mtx_len(command))
	{
		ret[i] = var_content_elab(command[i], mini->env);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

static void	absolute_cmd(char **command, t_mini *mini)
{
	char	*exe_path;

	exe_path = var_ex(command[0], '\0');
	if (execve(exe_path, command, mini->env) == -1)
		free(exe_path);
	rl_clear_history();
}

void	execve_cmd(char **command, t_mini *mini)
{
	char	**path;
	char	*exe_path;
	char	**elab_cmd;

	if (access(command[0], X_OK) == 0)
		absolute_cmd(command, mini);
	path = path_finder(mini->env);
	if (!path)
		no_path(command[0], mini);
	elab_cmd = command_elab(command, mini);
	exe_path = cmd_check(path, elab_cmd[0]);
	mtxs_free(path);
	if (!exe_path)
	{
		mtxs_free(elab_cmd);
		free_mini(mini);
		exit (1);
	}
	rl_clear_history();
	if (execve(exe_path, elab_cmd, mini->env) == -1)
		free(exe_path);
	mtxs_free(elab_cmd);
}

void	ft_execute_command(char **command, t_mini *mini)
{
	if (control_bt(command[0]) == 1)
		exe_bt(command, mini);
	else
		execve_cmd(command, mini);
}
