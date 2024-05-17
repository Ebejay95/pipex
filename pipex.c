/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/17 08:23:48 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

int	opern_in_out(int argc, char **argv, int *fd_in, int *fd_out)
{
	*fd_in = open(argv[1], O_RDONLY);
	*fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_in == -1 || *fd_out == -1)
		return (-1);
	return (0);
}

// TODO here_docs
//int	main(int argc, char **argv, char **envp)
//{
//	int	fd_in;
//	int	fd_out;
//	int	tube[2];
//	int	prevpipe;
//	int	process;
//	int	i;
//	int	status;
//	int	exitcode;
//
//	if (argc < 5)
//	{
//		ft_putstr_fd(STDERR_FILENO, "[input] [cmd1] ... [cmdn] [output]\n");
//		return (1);
//	}
//	if (ft_strcmp(argv[1], "here_doc") == 0)
//	{
//		ft_printf("here_doc\n");
//		return (0);
//	}
//	if (opern_in_out(argc, argv, &fd_in, &fd_out) == -1)
//		return (ft_putstr_fd(STDERR_FILENO, "Error opening file\n"), 1);
//	i = 2;
//	prevpipe = fd_in;
//	while (i < (argc - 1))
//	{
//		if (pipe(tube) == -1)
//			return (ft_putstr_fd(STDERR_FILENO, "Error opening pipe\n"), 1);
//		process = fork();
//		if (process == -1)
//			return (ft_putstr_fd(STDERR_FILENO, "Error forking\n"), 1);
//		if (process == 0)
//		{
//			if (prevpipe != -1)
//			{
//				dup2(prevpipe, 0);
//				close(prevpipe);
//			}
//			if (i < (argc - 2))
//				dup2(tube[1], 1);
//			else
//				dup2(fd_out, 1);
//			close(tube[0]);
//			close(tube[1]);
//			exit(ft_execve(argv[i], envp));
//		}
//		else
//		{
//			close(tube[1]);
//			if (prevpipe != fd_in)
//				close(prevpipe);
//			prevpipe = tube[0];
//			wait(&status);
//			if (WIFEXITED(status))
//				exitcode = WIFEXITED(status);
//		}
//		i++;
//	}
//	if (prevpipe != -1)
//		close(prevpipe);
//	close(fd_in);
//	close(fd_out);
//	return (0);
// }


//int	main(int argc, char **argv, char **envp)
//	int fd_in;
//	int fd_out;
//	if (argc < 5)
//	{
//		ft_printf("\033[31margs must follow the order: [inputfile] [comand1] ... [commandn] [outputfile]\033[0m\n");
//		return (1);
//	}
//	fd_in = open(argv[1], O_RDONLY);
//	fd_out = open(argv[(argc - 1)], O_WRONLY | O_CREAT, 0644);
//	dup2(fd_in, 0);
//	close(fd_in);
//	close(fd_out);
//	char *test;
//	test = ft_strdup("awk '{print $3 \"\t\" $4}'");
//	ft_exc_args(test, retrieve_bsc_command(test, "", ""));
//	if(execve(ft_exc_path(retrieve_bsc_command(test, "/", ""), envp), ft_exc_args(test, retrieve_bsc_command(test, "", "")), envp) == -1)
//	{
//		ft_putstr_fd(STDERR_FILENO, "execve");
//		return (EXIT_FAILURE);
//	}
//	if(execve(ft_exc_path(retrieve_bsc_command("cat", "/", ""), envp), ft_exc_args("cat", retrieve_bsc_command("cat", "", "")), envp) == -1)
//	{
//		ft_putstr_fd(STDERR_FILENO, "execve");
//		return (EXIT_FAILURE);
//	}
//	return (0);
//}

//int main(int argc, char **argv, char **envp)
//{
//	(void)argc;
//	(void)argv;
//    char *commands[] = {
//        "awk \'\"{count++} END {print count}\"\'",
//        "awk \"{count++} END {print count}\"",
//        "awk '\"{count++} END {print count}\"'",
//        "awk \"'{count++} END {print count}'\"",
//        "awk \'\"{count++} END {print count}\"\'",
//        "\'\"{count++} END {print count}\"\'",
//        "\"{count++} END {print count}\"",
//        "'\"{count++} END {print count}\"'",
//        "\"'{count++} END {print count}'\"",
//        "\'\"{count++} END {print count}\"\'",
//        NULL
//    };
//
//    for (int k = 0; commands[k] != NULL; k++)
//    {
//        char **args = ft_exc_args_awk(commands[k], envp);
//		ft_printf("reference: %s\n", check_and_extract_quotes(commands[k]));
//        printf("Testing command: %s\n", commands[k]);
//        for (int i = 0; args[i] != NULL; i++)
//        {
//            printf("args[%d]: %s\n", i, args[i]);
//        }
//
//        // Freigeben der Argumente
//        for (int i = 0; args[i] != NULL; i++)
//        {
//            //free(args[i]);
//        }
//        //free(args);
//        printf("\n");
//    }
//
//    return 0;
//}

int is_escape_char(char c) {
	return c == '"' || c == '\\' || c == '/' || c == '\b' || c == '\f' || c == '\n' || c == '\r' || c == '\t';
}

int	is_escaped(const char *str, size_t pos)
{
	if (pos == 0)
		return (0);
	return (str[pos -1] == '\\');
}

char	*ft_escape(const char *str)
{
	size_t	i;
	size_t	j;
	size_t	len;
	size_t	new_len;
	char	*escaped;

	len = ft_strlen(str);
	new_len = len;
	i = 0;
	while (i < len)
	{
		if (is_escape_char(str[i]) && !is_escaped(str, i))
			new_len++;
		i++;
	}
	escaped = malloc(new_len + 1);
	if(!escaped)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (is_escape_char(str[i]) && !is_escaped(str, i))
		{
			escaped[j] = '\\';
			j++;
		}
		escaped[j] = str[i];
		j++;
		i++;
	}
	escaped[j] = '\0';
	return (escaped);
}
