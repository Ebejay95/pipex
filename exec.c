/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:06:49 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/20 07:18:21 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

#include <stdlib.h>
#include <string.h>

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

char	**ft_exc_args(char *full_cmd)
{
	return (ft_split(full_cmd, ' '));
}

int	ft_execve(char *command, char **envp)
{
	char	*path;
	char	**args;

	path = ft_exc_path(retrieve_bsc_command(command, "/", ""), envp);
	args = ft_exc_args(command);
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
