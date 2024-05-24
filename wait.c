/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:16:37 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/24 15:17:53 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	wait_for_here_doc(t_args *args, t_processes *prcs)
{
	int	i;
	int	status;
	int	exit_code;

	status = 0;
	exit_code = 0;
	i = 0;
	while (i < args->c - 4)
	{
		if (waitpid(prcs->track[i], &status, 0) == -1)
		{
			perror("Error waiting for process");
			exit_code = EXIT_FAILURE;
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_code);
}

int	wait_for_processes(t_args *args, t_processes *prcs)
{
	int	i;
	int	status;
	int	exit_code;

	status = 0;
	exit_code = 0;
	i = 0;
	while (i < args->c - 3)
	{
		if (waitpid(prcs->track[i], &status, 0) == -1)
		{
			perror("Error waiting for process");
			exit_code = EXIT_FAILURE;
		}
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status);
		i++;
	}
	return (exit_code);
}

int	wait_handling(t_args *args, t_processes *prcs)
{
	if (ft_strcmp(args->v[1], "here_doc") == 0)
		return (wait_for_here_doc(args, prcs));
	else
		return (wait_for_processes(args, prcs));
}
