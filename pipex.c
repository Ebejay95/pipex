/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/20 09:18:32 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	save_hd_input(char **argv)
{
	char	buffer[BUFFER_SIZE];
	int		readchar;
	int		tmp;

	tmp = open("hd.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp == -1)
		return (-1);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		readchar = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
		if (readchar == -1)
			return (-1);
		buffer[readchar] = '\0';
		if (ft_strncmp(buffer, argv[2], ft_strlen(argv[2])) == 0)
		{
			if (buffer[ft_strlen(argv[2])] == '\n')
				break ;
		}
		write(tmp, buffer, readchar);
	}
	close(tmp);
	return (0);
}

int	open_in_out(int argc, char **argv, int *fd_in, int *fd_out)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		if (save_hd_input(argv) == -1)
			return (-1);
		*fd_in = open("hd.tmp", O_RDONLY);
		if (*fd_in == -1)
			return (-1);
	}
	else
	{
		*fd_in = open(argv[1], O_RDONLY);
		if (*fd_in == -1)
			return (-1);
	}
	*fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		close(*fd_in);
		return (-1);
	}
	return (0);
}

int	get_initial_index(char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (3);
	return (2);
}

void	wait_handling(int argc, char **argv, int processes[])
{
	int	i;

	i = 0;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		while (i < argc - 4)
		{
			waitpid(processes[i], NULL, 0);
			i++;
		}
	}
	else
	{
		while (i < argc - 3)
		{
			waitpid(processes[i], NULL, 0);
			i++;
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	tube[2];
	int	prevpipe;
	int	process;
	int	i;
	int	processes[OPEN_MAX];

	if (argc < 5)
	{
		ft_putstr_fd(STDERR_FILENO, "[input] [cmd1] ... [cmdn] [output]\n");
		return (1);
	}
	if (open_in_out(argc, argv, &fd_in, &fd_out) == -1)
		return (ft_putstr_fd(STDERR_FILENO, "Error opening file\n"), 1);
	i = get_initial_index(argv);
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
			ft_execve(argv[i], envp);
			ft_putstr_fd(STDERR_FILENO, "Error executing\n");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (ft_strcmp(argv[1], "here_doc") == 0)
				processes[i - 3] = process;
			else
				processes[i - 2] = process;
			close(tube[1]);
			if (prevpipe != fd_in)
				close(prevpipe);
			prevpipe = tube[0];
		}
		i++;
	}
	if (prevpipe != -1)
		close(prevpipe);
	close(fd_in);
	close(fd_out);
	wait_handling(argc, argv, processes);
	return (0);
}
