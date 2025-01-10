/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:06:15 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 11:06:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expand(t_cmd *cur, t_data *data, int i)
{
	int	j;

	data->temp = malloc(ft_strlen(cur->cmd) + ft_strlen(data->env_var) + 1);
	if (!data->temp)
		exit (write(2, "Panic: malloc failed\n", 21));
	while (cur->cmd[++i] != '$')
		data->temp[i] = cur->cmd[i];
	j = 0;
	while (data->env_var[j])
	{
		data->temp[i + j] = data->env_var[j];
		j++;
	}
	while (cur->cmd[i + ft_strlen(data->env_name) + 1])
	{
		data->temp[i + j] = cur->cmd[i + ft_strlen(data->env_name) + 1];
		i++;
	}
	data->temp[i + j] = '\0';
	free(cur->cmd);
	free(data->env_name);
	free(data->env_var);
	data->env_var = NULL;
	cur->cmd = data->temp;
}

static void	need_to_expand(t_main *main, t_cmd *cur, t_data *data)
{
	while (cur->cmd[data->i] != '\0' && cur->cmd[data->i] != '$'
		&& cur->cmd[data->i] != ' ' && cur->cmd[data->i] != '\''
		&& cur->cmd[data->i] != '\"')
		data->i++;
	if (cur->cmd[data->i] == '$' || cur->cmd[data->i] == ' '
		|| cur->cmd[data->i] == '\'' || cur->cmd[data->i] == '\"')
		data->i--;
	data->env_name = ft_substr(cur->cmd, data->j, data->i - data->j + 1);
	data->env_var = pick_env(main, data->env_name);
	if (data->env_var == NULL)
		data->env_var = ft_strjoin("\0", "\0");
	expand(cur, data, - 1);
}

char	*env_expander(t_main *main, t_cmd *cur, t_data data)
{
	while (cur->cmd[data.i] != '\0')
	{
		if (cur->[data.i] == '\'' && data.dquote == 0)
			data.quote = 1;
		if (cur->cmd[data.i] == '\"' && data.quote == 0)
			data.dquote = 1;
		if (cur->cmd[data.i] == '$' && data.quote == 0)
		{
			data.i++;
			data.j = data.i;
			if (cur->cmd[data.i] == '?')
			{
				data.env_name = ft_substr(cur->cmd, data.j, data.i - data.j + 1);
				data.env_var = ft_itoa(g_code_exit);
				if (data.env_var != NULL)
					expand(cur, &data, -1);
			}
			else
				need_to_expand(main, cur, &data);
			data.i = 0
		}
		if (cur->cmd[data.i] != '\0')
			data.i++;
	}
	return (cur->cmd);
}
