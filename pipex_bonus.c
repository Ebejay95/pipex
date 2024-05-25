/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:08:08 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/25 22:36:12 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

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

int	main(int argc, char **argv, char **envp)
{
	t_fds		fds;
	t_processes	prcs;
	t_args		args;
	int			exit_code;

	exit_code = 0;
	if (initialize(&args, &fds, argc, argv) != 0)
		return (1);
	if (prcss_cmmnds(&args, &fds, &prcs, envp) != 0)
		return (1);
	if (clear_end(&args, &fds) != 0)
		return (1);
	exit_code = wait_handling(&args, &prcs);
	return (exit_code);
}
