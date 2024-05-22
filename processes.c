/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 10:00:06 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/22 15:33:49 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	init_pipes(int *tube)
{
	if (pipe(tube) == -1)
		handle_error("Error opening pipe\n");
}

int	create_process(void)
{
	int	process;

	process = fork();
	if (process == -1)
		handle_error("Error forking\n");
	return (process);
}

void	child_process(t_params *params, char *cmd, char **envp)
{
	if (params->prevpipe != -1)
	{
		dup2(params->prevpipe, 0);
		close(params->prevpipe);
	}
	if (!params->is_last_command)
		dup2(params->tube[1], 1);
	else
		dup2(params->fd_out, 1);
	close(params->tube[0]);
	close(params->tube[1]);
	ft_execve(cmd, envp);
	handle_error("Error executing\n");
}

void	parent_process(t_params *params, int process, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		params->processes[params->process_index - 3] = process;
	else
		params->processes[params->process_index - 2] = process;
	close(params->tube[1]);
	if (params->prevpipe != -1)
		close(params->prevpipe);
	params->prevpipe = params->tube[0];
}

void	process_loop(int argc, char **argv, char **envp, t_params *params)
{
	int	process;
	int	i;

	i = get_initial_index(argv);
	params->prevpipe = params->fd_in;
	while (i < (argc - 1))
	{
		init_pipes(params->tube);
		process = create_process();
		params->is_last_command = (i == (argc - 2));
		params->process_index = i;
		if (process == 0)
			child_process(params, argv[i], envp);
		else
			parent_process(params, process, argv);
		i++;
	}
	if (params->prevpipe != -1)
		close(params->prevpipe);
}
