/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:08:30 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/25 22:25:32 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

int	handle_here_doc(t_args *a)
{
	if (save_hd_input(a->v) == -1)
	{
		perror("Error saving heredoc input");
		return (-1);
	}
	return (open("hd.tmp", O_RDONLY));
}

int	open_input_file(t_args *a)
{
	if (ft_strcmp(a->v[1], "here_doc") == 0)
	{
		return (handle_here_doc(a));
	}
	else
	{
		return (open(a->v[1], O_RDONLY));
	}
}

int	open_output_file(t_args *args)
{
	char	*possible_heredoc;
	char	*limiter;

	possible_heredoc = args->v[1];
	limiter = args->v[args->c - 1];
	if (ft_strcmp(possible_heredoc, "here_doc") == 0)
		return (open(limiter, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0644));
	else
		return (open(limiter, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

int	open_in_out(t_args *a, t_fds *fds)
{
	char	*retstr;

	retstr = ft_strdup("pipex: input: No such file or directory\n");
	fds->in = open_input_file(a);
	if (fds->in == -1)
	{
		ft_putstr_fd(STDERR_FILENO, retstr);
		fds->in = -1;
		free(retstr);
		return (-1);
	}
	free(retstr);
	fds->out = open_output_file(a);
	if (fds->out == -1)
	{
		ft_putstr_fd(STDERR_FILENO, "Error opening output file: \n");
		if (fds->in != -1)
			close(fds->in);
		return (-1);
	}
	return (0);
}
