/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:12:47 by marvin            #+#    #+#             */
/*   Updated: 2025/01/24 11:12:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// Funzione di utilità per copiare una stringa
static void	ft_strcpy(char *dest, const char *src) {
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

// Funzione di utilità per concatenare due stringhe
static void	ft_strcat(char *dest, const char *src)
{
	while (*dest)
	{
		dest++;
	}
	while (*src)
	{
		*dest++ = *src++;
	}
	*dest = '\0';
}

// Funzione per aggiungere o aggiornare una variabile d'ambiente
int	builtin_export(char *arg)
{
	if (arg == NULL) {
		write(STDERR_FILENO, "Usage: export VAR=VALUE\n", 24);
		return 1;
	}
	char *equal_sign = strchr(arg, '=');
	if (equal_sign == NULL) {
		write(STDERR_FILENO, "Usage: export VAR=VALUE\n", 24);
		return 1;
	}
	*equal_sign = '\0';
	char *var = arg;
	char *value = equal_sign + 1;
	// Costruisce la stringa VAR=VALUE
	size_t var_len = strlen(var);
	size_t value_len = strlen(value);
	char *env_entry = malloc(var_len + value_len + 2);
	if (env_entry == NULL) {
		write(STDERR_FILENO, "Error: malloc failed\n", 21);
		return 1;
	}
    // Copia var e value in env_entry
	ft_strcpy(env_entry, var);
	ft_strcat(env_entry, "=");
	ft_strcat(env_entry, value);
    // Aggiunge o aggiorna la variabile d'ambiente
	if (putenv(env_entry) != 0) {
		write(STDERR_FILENO, "Error: putenv failed\n", 21);
		free(env_entry);
		return 1;
	}
    // Non liberare env_entry, poiché putenv utilizza il puntatore direttamente
	return 0;
}
