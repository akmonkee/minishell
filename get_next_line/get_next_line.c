/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 10:27:50 by msisto            #+#    #+#             */
/*   Updated: 2025/01/21 10:42:30 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen_g(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strjoin(char *line, char *buf)
{
	int		i;
	int		c;
	char	*fstr;

	if (!buf)
		return (NULL);
	fstr = malloc(ft_strlen_g(line) + ft_strlen_g(buf) + 1);
	if (!fstr)
		return (NULL);
	i = 0;
	c = 0;
	while (line && line[i])
		fstr[c++] = line[i++];
	i = 0;
	while (buf && buf[i])
		fstr[c++] = buf[i++];
	fstr[c] = '\0';
	free(line);
	return (fstr);
}

char	*print_out(char *ret)
{
	char	*output;
	int		i;

	i = 0;
	if (ret[0] == '\0')
		return (NULL);
	while (ret[i] && ret[i] != '\n')
		i++;
	output = malloc(i + 2);
	if (!output)
		return (NULL);
	i = -1;
	while (ret[++i] && ret[i] != '\n')
		output[i] = ret[i];
	if (ret[i] == '\n')
	{
		output[i] = '\n';
		i++;
	}
	output[i] = '\0';
	return (output);
}

char	*update_ret(char *ret)
{
	int		i;
	int		k;
	char	*temp;

	k = 0;
	i = 0;
	if (!ret)
		return (NULL);
	while (ret[i] && ret[i] != '\n')
		i++;
	if (!ret[i])
	{
		free(ret);
		return (NULL);
	}
	temp = malloc(ft_strlen_g(ret) - i + 1);
	if (!temp)
		return (free(ret), NULL);
	i++;
	k = 0;
	while (ret[i])
		temp[k++] = ret[i++];
	temp[k] = '\0';
	return (free(ret), temp);
}

char	*get_next_line(int fd, int i2)
{
	char			*output;
	static char		buf[BUFFER_SIZE + 1];
	static char		*ret;
	int				i;

	if (BUFFER_SIZE < 1 || fd < 0)
		return (NULL);
	i = 1;
	if (i2 == 0)
		return (free(ret), NULL);
	while (!ft_strchr_g(ret, '\n') && i > 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
		{
			free(ret);
			return (NULL);
		}
		ret = gnl_strjoin(ret, buf);
		ft_in_array(buf);
	}
	output = print_out(ret);
	ret = update_ret(ret);
	return (return_fun(output));
}
