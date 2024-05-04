/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/04 22:40:47 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"
#include <stdio.h>


//int main(int argc, char **argv)
//{
//	int p1[2];
//	if(pipe(p1) == -1)
//		return (1);
//	int id = fork();
//	if (id == -1)
//		return (1);
//	if (pid == 0)
//	{
//		int x;
//		if(read(p1[0, &x, sizeof(x)]) == -1)
//			return (1);
//		x = x * 4;
//		if (write(p1[1], &x, sizeof(x)) == -1)
//			return (1);
//	}
//	
//	return (0);
//}

//int	main (void)
//{
//	int id;
//	int status;
//	int fd[2];
//	pipe(fd);
//	id = fork();
//	if(id == 0)
//	{
//		close(fd[0]);
//		int x;
//		printf("Input a number: ");
//		scanf("%d", &x);
//		write(fd[1], &x, sizeof(int));
//		close(fd[1]);
//	}
//	else
//	{
//		int y;
//		close(fd[1]);
//		wait(&status);
//		read(fd[0], &y, sizeof(int));
//		close(fd[1]);
//		printf("U entered number: %i\n", y);
//	}
//	return (0);
//}

//int	main (void)
//{
//	int id;
//	int n;
//	int p;
//	int status;
//
//	id = fork();
//	if(id == 0)
//		n = 1;
//	else
//		n = 6;
//	p = n;
//	if (id != 0)
//		wait(&status);
//	while (p < (n + 5))
//	{
//		ft_printf("%i ", p);
//		p++;
//		if (id == 0)
//			exit(5);
//	}
//	if (id != 0)
//		ft_printf("\n");
//	return (0);
//}

//int	get_input(char *filename, char *filecontent)
//{
//	int		fd;
//	char	*line;
//	fd = open(filename, O_RDONLY);
//	if (fd == -1)
//	{
//		free(*filecontent);
//		return (0);
//	}
//	while (1)
//	{
//		line = get_next_line(fd);
//		if (line == NULL)
//		{
//			filename = *filecontent;
//			close(fd);
//			return (1);
//		}
//		*filecontent = ft_strjoin(*filecontent, line);
//		if (*filecontent == NULL)
//			return (0);
//		free(line);
//	}
//	return (0);
//}

//int	process_args(int argc, char **argv, char *inputfilecontent)
//{
//	if (argc != 5)
//	{
//		ft_printf("args must follow the order: [inputfile] [comand1] [command2] [outputfile]\n");
//		return (1);
//	}
//	if (get_input(argv[1], &inputfilecontent) == 0)
//	{
//		ft_printf("\033[31m[inputfile]: %s - does not exist, or cannot be read from\033[0m\n", argv[1]);
//		return (1);
//	}
//	ft_printf("RETRUN: %s\n", argv[1]);
//	return (0);
//}

char *get_file_content(char *filename)
{
	char	*filecontent;
	char	*tmp;
	char	*line;
	int		fd;

	filecontent = ft_strdup("");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("File %s does not exist, or cannot be read from\n", filename);
		return (filecontent);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		tmp = ft_calloc(sizeof(char), (ft_strlen(line) + ft_strlen(filecontent) + 1));
		if(tmp == NULL)
		{
			free(line);
			close(fd);
			return (filecontent);
		}
		free(filecontent);
		ft_strcpy(tmp, filecontent);
		ft_strcat(tmp, line);
		filecontent = tmp;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (filecontent);
}

//void	perform_pipex(char **argv)
//{
//	int	pid;
//
//	pid = fork();
//
//	if (pid == 0)
//	{
//
//	}
//	else
//	{
//		
//	}
//	//ft_printf("PIPEX:\n");
//	//ft_printf("\tinput: %s\n", get_file_content(argv[1]));
//	//ft_printf("\toutput: %s\n", argv[2]);
//	//ft_printf("\tcommand1: %s\n", argv[3]);
//	//ft_printf("\tcommand2: %s\n", argv[4]);
//
//}

//int main(int argc, char **argv)
//{
//	//char *inputfilecontent;
////
//	//inputfilecontent = NULL;
//	//if(process_args(argc, argv, inputfilecontent) == 1)
//	//	return (0);
//	if (argc != 5)
//	{
//		ft_printf("\033[31margs must follow the order: [inputfile] [comand1] [command2] [outputfile]\033[0m\n");
//		return (1);
//	}
//	perform_pipex(argv);
//	//if(argc == 2)
//	//{
//	//	int fd;
//	//
//	//	fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
//	//	dup2(fd, STDOUT_FILENO);
//	//	close(fd);
//	//}
//	return (0);
//}

int opener(char *filename)
{
	int	fd;

	if(filename != NULL)
	{
		if(access(filename, R_OK) != -1)
		{
			fd = open(filename, O_WRONLY | O_CREAT, 0644);
			return (fd);
		}
		return (-1);
	}
	return (-1);
}


void	prtintenv(char **env)
{
	int	envdx;
	char	*print;

	envdx = 0;
	while (env[envdx] != 0)
	{
		print = ft_color(env[envdx], YELLOW);
		ft_printf(print);
		ft_printf("\n");
		free(print);
		envdx++;
	}
}

char *ft_get_envline(char *needle, char **envp)
{
	int		envdx;
	char	*pthl;
	char	*pthl_start;

	envdx = 0;
	while (envp[envdx] != 0)
	{
		pthl_start = ft_strstr(envp[envdx], needle);
		if (pthl_start == envp[envdx])
		{
			pthl = ft_calloc((ft_strlen(envp[envdx]) + 1), sizeof(char));
			if(pthl == NULL)
				return (NULL);
			ft_strcpy(pthl, envp[envdx]);
		}
		envdx++;
	}

	return (pthl);
}

void	ft_exc_path(char *exc, char **envp)
{
	char *pathline;
	char **paths;
	int		pathcount;
	int		i;

	paths = NULL;
	pathline = ft_get_envline("PATH", envp);
	if(pathline != NULL)
	{
		i = 0;
		pathcount = ft_count_words(pathline, ' ');
		paths = ft_split(pathline, ' '); // pointer number... 
		while (i < pathcount)
		{
			ft_printf(ft_color(pathline,GREEN));
			ft_printf("\n");
			ft_printf(ft_color(paths[i],BRIGHT_BLUE));
			ft_printf("\n");
			ft_printf(exc);
			ft_printf("\n");
			i++;
		}
	}
	free(pathline);
}

int main(int argc, char **argv, char **envp)
{
	int fd_in;
	int fd_out;
	int cmd_i;
	//int	fd[2];
	//int pid;
	//int prev_pfd;

	prtintenv(envp);
	if (argc < 5)
	{
		ft_printf("\033[31margs must follow the order: [inputfile] [comand1] ... [commandn] [outputfile]\033[0m\n");
		return (1);
	}
	fd_in = opener(argv[1]);
	fd_out = opener(argv[4]);
	cmd_i = 2;
	// unterstuetze auch den fall wenn kein inputfile existiert infile cat wc-l +> 0
	ft_printf("%i %i\n", fd_in, fd_out);
	if (fd_in >= 0 && fd_out >= 1)
	{
		//prev_pfd = fd_in;
		while (cmd_i < (argc - 1))
		{
			ft_printf("DO SHIT: %s\n", argv[cmd_i]);
		//	if (pipe(fd) == -1)
		//	{
		//		perror("pipe");
		//		exit(EXIT_FAILURE);
		//	}
		//	pid = fork();
		//	if (pid == -1)
		//	{
		//		perror("fork");
		//		exit(EXIT_FAILURE);
		//	}
		//	if (pid == 0)
		//	{
		//		dup2(prev_pfd, STDIN_FILENO);
		//		if(cmd_i < argc - 2)
		//			dup2(fd[1], STDOUT_FILENO);
		//		else
		//			dup2(fd_out, STDOUT_FILENO);
		//		close(fd[0]);
		//		close(fd[1]);
		//ft_exc_path(argv[cmd_i], envp);
		//execve(ft_exc_path(argv[cmd_i], envp), ft_exc_args(argv[cmd_i]), envp);

			char *args[3];

			args[0] = "echo";
			args[1] = "Rustam is a cool guy!!";
			args[2] = NULL;
		execve("/local/bin/echo", args, NULL);

		//execve(, array argv[1]);
		//		perror("exec failed");
		//		exit(EXIT_FAILURE);
		//	}
		//	close(fd[1]);
		//	if (prev_pfd != fd_in)
		//		close(prev_pfd);
		//	prev_pfd = fd[0];
			cmd_i++;
		}
		wait(NULL);
	}
	close(fd_in);
	close(fd_out);
	return (0);
}

// execute 


//int main(int argc, char **argv)
//{
//	if(argc == 3)
//	{
//		int fd;
//	
//		fd = open(argv[1], O_WRONLY | O_CREAT, 0644);
//		dup2(fd, STDOUT_FILENO);
//		close(fd);
//		ft_printf(argv[2]);
//	}
//	return (0);
//}

//int main(int argc, char **argv)
//{
//	if(argc == 2)
//	{
//		if(access(argv[1], R_OK) != -1)
//			ft_printf("erse");
//		else
//			ft_printf("dsfds");
//	}
//	return (0);
//}


// int main(void)
// {
// 	int	pid;

// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0)
// 	{
// 		ft_printf("child %i %i\n", pid, getpid());
// 	}
// 	else
// 	{
// 		ft_printf("main %i %i\n", pid, getpid());
// 	}
// 	return (0);
// }

// int main(void)
// {
// 	int	fd[2];
// 	int pid;
// 	char buffer[11];

// 	if (pipe(fd) == -1)
// 	{
// 		perror("pipe");
// 		exit(EXIT_FAILURE);
// 	}

// 	pid = fork();

// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(EXIT_FAILURE);
// 	}

// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		write(fd[1], "Hello parent!", 13);
// 		close(fd[1]);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		read(fd[0], buffer, 13);
// 		close(fd[0]);
// 		printf("Message from child: '%s'\n", buffer);
// 		exit(EXIT_SUCCESS);
// 	}
// 	return (0);
// }

// int main(int argc, char **argv)
// {
// 	if(argc == 2)
// 	{
// 		if(unlink(argv[1]) == 0)
// 			ft_printf("file %s deleted", argv[1]);
// 		else
// 			ft_printf("Error deleting file %s", argv[1]);
// 	}
// 	return (0);
// }

//int main(void)
//{
//	int pid;
//
//	pid = fork();
//	if (pid == -1)
//	{
//		perror("fork");
//		exit(EXIT_FAILURE);
//	}
//
//	if (pid == 0)
//	{
//		ft_printf("i am a child\n");
//		sleep(2);
//		exit(EXIT_SUCCESS);
//	}
//	else
//	{
//		ft_printf("i am a parent\n");
//		wait(NULL);
//		exit(EXIT_SUCCESS);
//	}
//	return (0);
//}

//ft_printf("\nWEXIT:%i WIFEXIT:%i", WEXITSTATUS(status), WIFEXITED(status));