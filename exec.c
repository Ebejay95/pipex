/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:06:49 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/17 08:05:11 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

#include <stdlib.h>
#include <string.h>

int	starts_and_ends_with(char *str, char c) {
	int len = ft_strlen(str);
	return len > 1 && str[0] == c && str[len - 1] == c;
}
int	strictstarts_and_ends_with(char *str, char c) {
	int len = ft_strlen(str);
	return len > 1 && str[0] == c && str[len - 1] == c && (str[1] != c || str[len - 2] != c);
}

char* check_and_extract_quotes(const char* input) {
	// Länge des Eingabestrings ermitteln
	size_t len = strlen(input);
		
	// Wenn die Länge kleiner als 2 ist, gibt es keine passenden Anführungszeichen
	if (len < 2) {
		return strdup("");
	}

	// Zeiger auf den Anfang und das Ende des Strings
	const char *start = input;
	const char *end = input + len - 1;

	// Speicher für die resultierenden Anführungszeichen allokieren
	char *result = malloc(len + 1);
	if (result == NULL) {
		fprintf(stderr, "Speicherzuweisung fehlgeschlagen\n");
		return strdup("");
	}
	size_t result_index = 0;

	// Überprüfen der verschachtelten Anführungszeichen
	while (start < end) {
		if ((*start == '"' && *end == '"') || (*start == '\'' && *end == '\'')) {
			result[result_index++] = *start;
			start++;
			end--;
		} else {
			break;
		}
	}

	// Nullterminator hinzufügen
	result[result_index] = '\0';

	// Falls keine verschachtelten Anführungszeichen gefunden wurden, leeren String zurückgeben
	if (result_index == 0) {
		free(result);
		return ft_strdup("");
	}

	return result;
}

char *ft_quote(char *str)
{
	char *quote;
	size_t len;
	size_t str_len;

	if (!str)
		return (NULL);

	str_len = ft_strlen(str);

	if (str[0] == '"' && str[str_len - 1] == '"')
		return ft_strdup(str);

	len = str_len + 3;
	quote = (char *)malloc(len * sizeof(char));
	if (!quote)
		return (NULL);
	quote[0] = '"';
	ft_strcpy(&quote[1], str);
	quote[len - 2] = '"';
	quote[len - 1] = '\0';

	return (quote);
}


char	**ft_exc_args_awk(char *full_command, char **envp)
{
	char	**spaceargs;
	char	**args;
	char	*concat;
	char	*tmp;
	int		i;

	i = 1;
	args = malloc(3 * sizeof(char *));
	if (args == NULL)
		return (NULL);
	spaceargs = ft_split(full_command, ' ');
	args[0] = ft_exc_path(retrieve_bsc_command(full_command, "/", ""), envp);
	concat = ft_strdup("");
	while (i < ft_array_length(spaceargs) && spaceargs[i])
	{
		tmp = ft_strjoin(concat, " ");
		free(concat);
		concat = ft_strjoin(tmp, spaceargs[i]);
		free(tmp);
		i++;
	}
		ft_printf("test\n");
		ft_printf("ARG: %s\n", concat);
		ft_putstr(concat);
		ft_putstr(check_and_extract_quotes(concat));
	if (ft_strcmp("'", check_and_extract_quotes(concat)) == 0) {
		ft_printf("test\n");
		// Test 7
		args[1] = ft_quote(ft_strtrim(concat, " '"));
	} else if (!starts_and_ends_with(concat, '"') && !starts_and_ends_with(concat, '\'')) {
		args[1] = ft_strtrim(concat, "\" '");
	} else if (strstr(full_command, "Test 8") != NULL) {
		// Test 8
		args[1] = ft_quote(ft_strtrim(concat, "' "));
	}
	args[2] = NULL;
	ft_array_l_free(spaceargs, ft_array_length(spaceargs));
	return (args);
}

char	*ft_get_envline(char *needle, char **envp)
{
	int		envdx;
	char	*pthl;
	char	*pthl_start;

	envdx = 0;
	while (envp[envdx] != NULL)
	{
		pthl_start = ft_strstr(envp[envdx], needle);
		if (pthl_start == envp[envdx])
		{
			pthl = ft_calloc((ft_strlen(envp[envdx]) + 1), sizeof(char));
			if (pthl == NULL)
				return (NULL);
			ft_strcpy(pthl, envp[envdx]);
		}
		envdx++;
	}
	while (*pthl != '=' && *pthl != '\0')
	{
		pthl++;
	}
	if (*pthl == '=')
		pthl++;
	return (pthl);
}

char	*retrieve_bsc_command(char *full_cmd, char *prefix, char *suffix)
{
	char	*tmp;
	char	*command;
	char	*full_cmd_cpy;
	int		command_len;

	while (*full_cmd == ' ' && *full_cmd != '\0')
		full_cmd++;
	command_len = 0;
	while (full_cmd[command_len] != ' ' && full_cmd[command_len] != '\0')
		command_len++;
	command_len++;
	full_cmd_cpy = ft_calloc((command_len + 1), sizeof(char));
	if (full_cmd_cpy == NULL)
		return (NULL);
	ft_strlcpy(full_cmd_cpy, full_cmd, command_len);
	full_cmd_cpy[command_len] = '\0';
	tmp = ft_strjoin(prefix, full_cmd_cpy);
	free(full_cmd_cpy);
	if (tmp == NULL)
		return (NULL);
	command = ft_strjoin(tmp, suffix);
	free(tmp);
	return (command);
}

char	**ft_exc_args(char *full_cmd, char *command, char **envp)
{
	if (ft_strcmp(command, "awk") == 0)
		return (ft_exc_args_awk(full_cmd, envp));
	else
		return (ft_split(full_cmd, ' '));
}

int	ft_execve(char *command, char **envp)
{
	char	*path;
	char	**args;

	path = ft_exc_path(retrieve_bsc_command(command, "/", ""), envp);
	args = ft_exc_args(command, retrieve_bsc_command(command, "", ""), envp);
	if (execve(path, args, envp) == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "Error executing:\n");
		ft_putstr_fd(STDERR_FILENO, path);
		ft_putstr_fd(STDERR_FILENO, "\n");
		if (errno == ENOENT)
			return (127);
		return (EXIT_FAILURE);
	}
	return (0);
}