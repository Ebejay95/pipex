/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:19:27 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/23 10:22:55 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	wait_handling(t_args *args, t_processes *prcs)
{
	int	i;

	i = 0;
	if (ft_strcmp(args->v[1], "here_doc") == 0)
	{
		while (i < args->c - 4)
		{
			waitpid(prcs->track[i], NULL, 0);
			i++;
		}
	}
	else
	{
		while (i < args->c - 3)
		{
			waitpid(prcs->track[i], NULL, 0);
			i++;
		}
	}
}

void	child_process(t_fds *fds, t_args *args, char **envp)
{
	if (fds->prevpipe != -1)
	{
		dup2(fds->prevpipe, 0);
		close(fds->prevpipe);
	}
	if (args->i < (args->c - 2))
		dup2(fds->tube[1], 1);
	else
		dup2(fds->fd_out, 1);
	close(fds->tube[0]);
	close(fds->tube[1]);
	ft_execve(args->v[args->i], envp);
	ft_putstr_fd(STDERR_FILENO, "Error executing\n");
	exit(EXIT_FAILURE);
}

void	main_process(t_processes *prcs, t_fds *fds, t_args *args)
{
	if (ft_strcmp(args->v[1], "here_doc") == 0)
		prcs->track[args->i - 3] = prcs->current;
	else
		prcs->track[args->i - 2] = prcs->current;
	close(fds->tube[1]);
	if (fds->prevpipe != fds->fd_in)
		close(fds->prevpipe);
	fds->prevpipe = fds->tube[0];
}

void	do_pipe_act(t_processes *prcs, t_fds *fds, t_args *args, char **envp)
{
	if (prcs->current == 0)
		child_process(fds, args, envp);
	else
		main_process(prcs, fds, args);
}

int	prepare_piping(t_processes *prcs, t_fds *fds)
{
	if (pipe(fds->tube) == -1)
		return (ft_putstr_fd(STDERR_FILENO, "Error opening pipe\n"), 1);
	prcs->current = fork();
	if (prcs->current == -1)
		return (ft_putstr_fd(STDERR_FILENO, "Error forking\n"), 1);
	return (0);
}
