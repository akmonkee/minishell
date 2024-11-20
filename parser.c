/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 11:34:51 by msisto            #+#    #+#             */
/*   Updated: 2024/11/20 12:47:54 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	input_len(char	*input)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i] && input[i] <= 32 && input[i] >= 0)
		i++;
	while (input[i])
	{
		if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z') || (input[i] <= '9' && input[i] >= '0'))
			len++;
		if (i > 0 && (input[i] <= 32 && input[i] >= 0) && ((input[i - 1] >= 'A' && input[i - 1] <= 'Z') || (input[i - 1] >= 'a' && input[i - 1] <= 'z') || (input[i - 1] <= '9' && input[i - 1] >= '0')))
			len++;
		i++;
	}
	if (input[i - 1] <= 32 && input[i - 1] >= 0)
		len--;
	return (len);
}

void	input_cleaner(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = input_len(input);
	if (len <= 0)
		return ;
}
