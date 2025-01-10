/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:04:09 by marvin            #+#    #+#             */
/*   Updated: 2025/01/10 11:04:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rm_prefix(t_main *main, t_cmd *cur, int i)
{
	char	*temp;
	char	*temp2;
	char	**str;

	temp = pick_env(main, "PATH");
	if (temp[0] == '\0' && free_str(temp))
		return ;
	str = ft_split(temp, ':');
	temp2 = ft_strjoin(str[i], "/");
	while (str[i])
	{
		if (ft_strncmp(cur->cmd, temp2, ft_strlen(temp2)) == 0)
			cur->cmd = cur->cmd + ft_strlen(temp2);
		free(temp2);
		temp2 = ft_strjoin(str[i++], "/");
	}
	if (temp2)
		free(temp2);
	free_matrix(str);
}

static char *initialize_cmd(t_main *main, t_cmd *cur)
{
	t_data	data;

	rm_prefix(main, cur, 0);
	data.i = 0;
	data.j = 0;
	data.quote = 0;
	data.dquote = 0;
	data.env_var = NULL;
	data.env_name = NULL;
	return (env_expander(main, cur, data));
}

static int	arg_counter(char *s)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			word_count(&word, s, &i, '\'');
		else if (s[i] == '\"')
			word_count(&word, s, &i, '\"');
		else if (s[i] == ' ')
		{
			word++;
			while (s[i] != '\0' && s[i] == ' ')
				i++;
		}
		if (s[i] != '\0')
			i++;
	}
	return (word);
}

char	**take_args(t_main *main, t_cmd *cur, char *str)
{
	char	**matrix;
	int		i;
	int		word;

	str = initialize_cmd(main, cur);
	matrix = malloc(sizeof(char *) * (arg_counter(str) + 1));
	malloc_p(matrix);
	i = skip_space(0, str);
	word = 0;
	while (arg_counter(str) != word)
		which_utils(str, &i, &word, matrix);
	matrix[word] = NULL;
	return (env_redir(matrix));
}
