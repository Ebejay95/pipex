/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:18:50 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/24 16:39:51 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

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
	close(fds->in);
	close(fds->out);
	if (ft_strcmp(a->v[1], "here_doc") == 0)
	{
		if (unlink("hd.tmp") == -1)
			return (ft_putstr_fd(STDERR_FILENO, "Error deleting tmp\n"), -1);
	}
	return (0);
}

void	handle_input_error(int *tmp_fd, t_fds *fds)
{
	*tmp_fd = open("/dev/null", O_RDONLY);
	if (*tmp_fd == -1)
	{
		perror("Error opening /dev/null");
		close(fds->out);
	}
	else
	{
		fds->prevpipe = *tmp_fd;
	}
}

int	initialize(t_args *args, t_fds *fds, int argc, char **argv)
{
	int	tmp_fd;

	args->c = argc;
	args->v = argv;
	if (args->c < 5)
		return (ft_putstr_fd(2, "[in] [cmd1] . [cmdn] [out]\n"), 1);
	if (open_in_out(args, fds) == -1)
		return (1);
	args->i = get_initial_index(args->v);
	fds->prevpipe = fds->in;
	if (fds->in == -1)
	{
		handle_input_error(&tmp_fd, fds);
		if (tmp_fd == -1)
			return (1);
	}
	return (0);
}

int	prcss_cmmnds(t_args *args, t_fds *fds, t_processes *prcs, char **envp)
{
	while (args->i < (args->c - 1))
	{
		if (prepare_piping(prcs, fds) == 1)
			return (1);
		do_pipe_act(prcs, fds, args, envp);
		args->i++;
	}
	return (0);
}
