/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/15 17:00:40 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

// TODO here_docs
int	main(int argc, char **argv, char **envp)
{
	//int	fd_in;
	//int	fd_out;
	//int	tube[2];
	//int	process;
//
	//if (argc < 5)
	//{
	//	ft_printf("\033[31m[input] [comand1] ... [commandn] [output]\033[0m\n");
	//	return (1);
	//}
	//fd_in = open(argv[1], O_RDONLY);
	//fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT, 0644);
	//pipe(tube);
	//process = fork();
	//if (process == 0)
	//{
	//	close(tube[0]);
	//	dup2(fd_in, 0);
	//	dup2(tube[1], 1);
	//	close(fd_in);
	//	close(fd_out);
	//	close(tube[1]);
	//	if (ft_execve(argv[2], envp) == -1)
	//	{
	//		ft_putstr_fd(STDERR_FILENO, "execve");
	//		return (EXIT_FAILURE);
	//	}
	//}
	//else
	//{
	//	close(tube[1]);
	//	wait(NULL);
	//	dup2(tube[0], 0);
	//	dup2(fd_out, 1);
	//	close(fd_in);
	//	close(fd_out);
	//	close(tube[0]);
	//	if (ft_execve(argv[3], envp) == -1)
	//	{
	//		ft_putstr_fd(STDERR_FILENO, "execve");
	//		return (EXIT_FAILURE);
	//	}
	//}
	//return (0);
	//	int fd_in;
	//int fd_out;
	//if (argc < 5)
	//{
	//	ft_printf("\033[31margs must follow the order: [inputfile] [comand1] ... [commandn] [outputfile]\033[0m\n");
	//	return (1);
	//}
	//fd_in = open(argv[1], O_RDONLY);
	//fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT, 0644);
	//dup2(fd_in, 0);
	//close(fd_in);
	//close(fd_out);
	//char *test;
	//test = ft_strdup("awk '{print $3 \"\t\" $4}'");
	//ft_exc_args(test, retrieve_bsc_command(test, "", ""));
	//if(execve(ft_exc_path(retrieve_bsc_command(test, "/", ""), envp), ft_exc_args(test, retrieve_bsc_command(test, "", "")), envp) == -1)
	//{
	//	ft_putstr_fd(STDERR_FILENO, "execve");
	//	return (EXIT_FAILURE);
	//}
	//if(execve(ft_exc_path(retrieve_bsc_command("cat", "/", ""), envp), ft_exc_args("cat", retrieve_bsc_command("cat", "", "")), envp) == -1)
	//{
	//	ft_putstr_fd(STDERR_FILENO, "execve");
	//	return (EXIT_FAILURE);
	//}
	return (0);
}
