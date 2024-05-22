/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 09:58:51 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/22 15:32:58 by jeberle          ###   ########.fr       */
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
