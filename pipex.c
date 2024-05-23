/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/23 13:51:40 by jeberle          ###   ########.fr       */
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

int	open_in_out(t_args *a, t_fds *fds)
{
	if (ft_strcmp(a->v[1], "here_doc") == 0)
	{
		if (a->c < 6)
			return (ft_putstr_fd(2, "hd lim [in] [cmd1] . [cmdn] [out]\n"), -1);
		if (save_hd_input(a->v) == -1)
			return (-1);
		fds->fd_in = open("hd.tmp", O_RDONLY);
		if (fds->fd_in == -1)
			return (-1);
	}
	else
	{
		fds->fd_in = open(a->v[1], O_RDONLY);
		if (fds->fd_in == -1)
			return (-1);
		if (a->c < 5)
			return (ft_putstr_fd(2, "[in] [cmd1] . [cmdn] [out]\n"), -1);
	}
	fds->fd_out = open(a->v[(a->c - 1)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fds->fd_out == -1)
	{
		close(fds->fd_in);
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

int	clear_end(t_args *a, t_fds *fds)
{
	if (fds->prevpipe != -1)
		close(fds->prevpipe);
	close(fds->fd_in);
	close(fds->fd_out);
	if (ft_strcmp(a->v[1], "here_doc") == 0)
	{
		if (unlink("hd.tmp") == -1)
			return (ft_putstr_fd(STDERR_FILENO, "Error deleting tmp\n"), -1);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_fds		fds;
	t_processes	prcs;
	t_args		args;

	args.c = argc;
	args.v = argv;
	if (open_in_out(&args, &fds) == -1)
		return (ft_putstr_fd(STDERR_FILENO, "Error opening file\n"), 1);
	args.i = get_initial_index(args.v);
	fds.prevpipe = fds.fd_in;
	while (args.i < (args.c - 1))
	{
		if (prepare_piping(&prcs, &fds) == 1)
			return (1);
		do_pipe_act(&prcs, &fds, &args, envp);
		args.i++;
	}
	if (clear_end(&args, &fds) != 0)
		return (-1);
	wait_handling(&args, &prcs);
	return (0);
}
