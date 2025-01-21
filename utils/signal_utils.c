/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msisto <msisto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 11:37:45 by msisto            #+#    #+#             */
/*   Updated: 2025/01/17 11:37:59 by msisto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, "minipierpaolo> ", 15);
}

void	handle_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, "minipierpaolo> ", 15);
}
