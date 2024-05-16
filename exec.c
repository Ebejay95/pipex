/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:06:49 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/16 18:01:16 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	**ft_exc_args_awk(char *full_command)
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
	args[0] = ft_strdup(spaceargs[0]);
	concat = ft_strdup("");
	while (i < ft_array_length(spaceargs) && spaceargs[i])
	{
		tmp = ft_strjoin(concat, spaceargs[i]);
		free(concat);
		concat = tmp;
		i++;
	}
	args[1] = ft_strtrim(concat, " '");
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

char	**ft_exc_args(char *full_cmd, char *command)
{
	if (ft_strcmp(command, "awk") == 0)
		return (ft_exc_args_awk(full_cmd));
	else
		return (ft_split(full_cmd, ' '));
}

int	ft_execve(char *command, char **envp)
{
	char	*path;
	char	**args;

	path = ft_exc_path(retrieve_bsc_command(command, "/", ""), envp);
	args = ft_exc_args(command, retrieve_bsc_command(command, "", ""));
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
