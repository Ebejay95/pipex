/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/16 18:24:08 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	opern_in_out(int argc, char **argv, int *fd_in, int *fd_out)
{
	*fd_in = open(argv[1], O_RDONLY);
	*fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT, 0644);
	if (*fd_in == -1 || *fd_out == -1)
		return (-1);
	return (0);
}

// TODO here_docs
int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	tube[2];
	int	prevpipe;
	int	process;
	int	i;
	int	status;
	int	exitcode;

	if (argc < 5)
	{
		ft_putstr_fd(STDERR_FILENO, "[input] [cmd1] ... [cmdn] [output]\n");
		return (1);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		ft_printf("here_doc\n");
		return (0);
	}
	if (opern_in_out(argc, argv, &fd_in, &fd_out) == -1)
		return (ft_putstr_fd(STDERR_FILENO, "Error opening file\n"), 1);
	i = 2;
	prevpipe = fd_in;
	while (i < (argc - 1))
	{
		if (pipe(tube) == -1)
			return (ft_putstr_fd(STDERR_FILENO, "Error opening pipe\n"), 1);
		process = fork();
		if (process == -1)
			return (ft_putstr_fd(STDERR_FILENO, "Error forking\n"), 1);
		if (process == 0)
		{
			if (prevpipe != -1)
			{
				dup2(prevpipe, 0);
				close(prevpipe);
			}
			if (i < (argc - 2))
				dup2(tube[1], 1);
			else
				dup2(fd_out, 1);
			close(tube[0]);
			close(tube[1]);
			exit(ft_execve(argv[i], envp));
		}
		else
		{
			close(tube[1]);
			if (prevpipe != fd_in)
				close(prevpipe);
			prevpipe = tube[0];
			wait(&status);
			if (WIFEXITED(status))
				exitcode = WIFEXITED(status);
		}
		i++;
	}
	if (prevpipe != -1)
		close(prevpipe);
	close(fd_in);
	close(fd_out);
	return (0);
}
