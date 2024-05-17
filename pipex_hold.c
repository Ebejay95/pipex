/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_hold.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/17 05:05:06 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	open_in_out(int argc, char **argv, int *fd_in, int *fd_out)
{
	*fd_in = open(argv[1], O_RDONLY);
	if (*fd_in == -1)
	{
		perror("error opening file");
		return (-1);
	}
	*fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out == -1)
	{
		close(*fd_in);
		perror("error opening file");
		return (-1);
	}
	return (0);
}

int	apply_max_bytes(int fd, size_t max, int write_fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	charread;
	size_t	all;

	all = 0;
	while ((charread = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (all + charread > max)
			charread = max - all;
		if (write(write_fd, buffer, charread) != charread)
		{
			perror("wrtiing error\n");
			return (-1);
		}
		all = all + charread;
		if (all >= max)
			break ;
	}
	if (charread == -1)
	{
		perror("reading error\n");
		return (-1);
	}
	return (0);
}

void	child(char *cmd, char **envp, int in, int out)
{
	int		process;
	char	*path = ft_exc_path(retrieve_bsc_command(cmd, "", ""), envp);
	char	**args;

	if (!path)
	{
		perror("command not found\n");
		exit(EXIT_FAILURE);
	}
	args = ft_exc_args(cmd, retrieve_bsc_command(cmd, "", ""), envp);
	if (!args)
	{
		perror("command args error\n");
		free(path);
		exit(EXIT_FAILURE);
	}
	process = fork();
	if (process == -1)
	{
		perror("error forking\n");
		close(in);
		close(out);
		free(path);
		ft_array_free(args);
		exit(EXIT_FAILURE);
	}
	if (process == 0)
	{
		if (dup2(in, STDIN_FILENO) == -1 || dup2(out, STDOUT_FILENO) == -1)
		{
			perror("error dup 2\n");
			free(path);
			ft_array_free(args);
			exit(EXIT_FAILURE);
		}
		close(in);
		close(out);
		perror("Error excute\n");
		execve(path, args, envp);
		perror("Error excute\n");
		free(path);
		ft_array_free(args);
		exit(EXIT_FAILURE);
	}
	free(path);
	ft_array_free(args);
}

void	clear(int tube[2])
{
	close(tube[0]);
	close(tube[1]);
}

int	collect_processes(int numchildren)
{
	int	status;
	int	exit_status;
	int i;

	exit_status = 0;
	i = 0;
	while (i < numchildren)
	{
		if (wait(&status) == -1)
			perror("error wait\n");
		else if(WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_status = WEXITSTATUS(status);
		i++;
	}
	return (exit_status);
}

// TODO separate bonus
int	main(int argc, char **argv, char **envp)
{
	int	fd_in;
	int	fd_out;
	int	tube[2];
	int	prevpipe;
	int	i;
	int numchildren;
	int	exitstatus;

	numchildren = 0;
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
	if (open_in_out(argc, argv, &fd_in, &fd_out) == -1)
		return (1);
	i = 2;
	prevpipe = fd_in;
	while (i < (argc - 1))
	{
		if (pipe(tube) == -1)
		{
			perror("error creating pipe\n");
			close(fd_in);
			close(fd_out);
			return (1);
		}
		child(argv[i], envp, prevpipe, tube[1]);
		numchildren++;
		close(tube[1]);
		if (apply_max_bytes(prevpipe, MAX_BYTES, tube[0]) == -1)
		{
			clear(tube);
			close(fd_in);
			close(fd_out);
			return (1);
		}
		if (prevpipe != fd_in)
			close(prevpipe);
		prevpipe = tube[0];
		i++;
	}
	child(argv[argc - 2], envp, prevpipe, fd_out);
	numchildren++;
	close(prevpipe);
	close(fd_in);
	close(fd_out);
	exitstatus = collect_processes(numchildren);
	return (exitstatus);
}
