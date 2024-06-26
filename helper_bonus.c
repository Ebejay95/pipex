/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:09:19 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/25 22:25:24 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

int	child_process(t_fds *fds, t_args *args, char **envp)
{
	if (fds->prevpipe != -1)
	{
		dup2(fds->prevpipe, 0);
		close(fds->prevpipe);
	}
	if (args->i < (args->c - 2))
		dup2(fds->tube[1], 1);
	else
		dup2(fds->out, 1);
	close(fds->tube[0]);
	close(fds->tube[1]);
	exit(ft_execve(args->v[args->i], envp));
}

void	main_process(t_processes *prcs, t_fds *fds, t_args *args)
{
	if (ft_strcmp(args->v[1], "here_doc") == 0)
		prcs->track[args->i - 3] = prcs->current;
	else
		prcs->track[args->i - 2] = prcs->current;
	close(fds->tube[1]);
	if (fds->prevpipe != fds->in)
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
