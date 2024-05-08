/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/08 16:29:06 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"
#include <stdio.h>

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

int	ft_array_length(char **array)
{
	int	length;

	length = 0;
	while (array[length] != NULL)
		length++;
	return (length);
}

void	ft_array_free(char **array)
{
	int	length;

	if(array == NULL)
		return ;
	length = ft_array_length(array);
	length--;
	while (length >= 0 && array[length] != NULL)
	{
		free(array[length]);
		length--;
	}
	free(array);
}

char** ft_exc_args_awk(char *full_command)
{
	int	i;
	int	j;
	int	spaceargsnumber;
	char **spaceargs;
	char **args;
	char *tmp;
	char *tmpjoin;
	char *tail;

	spaceargsnumber = ft_count_words(full_command, ' ');
	spaceargs = ft_split(full_command, ' ');
	if (spaceargs == NULL)
		return (NULL);
	args = malloc(spaceargsnumber * sizeof(char *));
	if (args == NULL)
	{
		i = spaceargsnumber - 1;
		while (i >= 0)
		{
			//free(spaceargs[i]);
			i--;
		}
		//free(spaceargs);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (i < spaceargsnumber)
	{
		if(*(spaceargs[i]) == '\'')
		{
			tmp = spaceargs[i] + 1;
			while (i < (spaceargsnumber - 1))
			{
				i++;
				if(ft_strchr(spaceargs[i], '\''))
				{
					tmpjoin = ft_strjoin(tmp, " ");
					tail = ft_strdup(spaceargs[i]);
					tail[ft_strlen(spaceargs[i]) - 1] = '\0';
					tmp = ft_strjoin(tmpjoin, tail);
					free(tmpjoin);
					free(tail);
					break ;
				}
				else
				{
					tmpjoin = ft_strjoin(tmp, " ");
					tmp = ft_strjoin(tmpjoin, spaceargs[i]);
					free(tmpjoin);
				}
				tmp = tmpjoin;
			}
			args[j] = tmp;
			j++;
		}
		else
		{
			args[j] = ft_strdup(spaceargs[i]);
			j++;
		}
		i++;
	}
	args[j] = NULL;
	while (i > j)
	{
		//free(args[i]);
		i--;
	}
	i = spaceargsnumber - 1;
	while (i >= 0)
	{
		//free(spaceargs[i]);
		i--;
	}
	//free(spaceargs);
	return (args);
}


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


void	ft_putallenv(char **env)
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
	while (envp[envdx] != NULL)
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
	while(*pthl != '=' && *pthl != '\0')
	{
		pthl++;
	}
	if (*pthl == '=')
		pthl++;
	return (pthl);
}

char	*ft_exc_path(char *exc, char **envp)
{
	char *pathline;
	char *joined;
	char **paths;
	int		pathcount;
	int		i;
	int		j;

	paths = NULL;
	pathline = ft_get_envline("PATH", envp);
	if(pathline != NULL)
	{
		i = 0;
		pathcount = ft_count_words(pathline, ':');
		paths = ft_split(pathline, ':');
		while (i < pathcount)
		{
			printf("---\n");
			printf("%s\n", paths[i]);
			printf("%s\n", exc);
			joined = ft_strjoin(paths[i], exc);
			if(joined == NULL)
				break ;

			if (access(joined, X_OK) == 0) {
				//free(pathline);
				j = 0;
				while (j < pathcount)
				{
					//free(paths[j]);
					j++;
				}
				//free(paths);
				return (joined);
			}
			i++;
			//free(joined);
		}
	}
	if(paths != NULL)
	{
		j = 0;
		while (j < pathcount)
		{
			//free(paths[j]);
			j++;
		}
		//free(paths);
	}
	//free(pathline);
	return (NULL);
}

char	*retrieve_bsc_command(char *full_command, char *prefix, char *suffix)
{
	char	*tmp;
	char	*command;
	char	*full_command_cpy;
	int		command_len;
	
	while (*full_command == ' ' && *full_command != '\0')
		full_command++;
	command_len = 0;
	while (full_command[command_len] != ' ' && full_command[command_len] != '\0')
		command_len++;
	command_len++;
	full_command_cpy = ft_calloc((command_len + 1), sizeof(char));
	if(full_command_cpy == NULL)
		return (NULL);
	ft_strlcpy(full_command_cpy, full_command, command_len);
	full_command_cpy[command_len] = '\0';
	tmp = ft_strjoin(prefix, full_command_cpy);
	free(full_command_cpy);
	if(tmp == NULL)
		return (NULL);
	command = ft_strjoin(tmp, suffix);
	free(tmp);
	return (command);
}

char	**ft_exc_args(char *full_command, char *command)
{
	if(ft_strcmp(command, "awk") == 0)
		return ft_exc_args_awk(full_command);
	else
		return ft_split(full_command, ' ');
}

int main(int argc, char **argv, char **envp)
{
	int fd_in;
	int fd_out;
	int cmd_i;
	int	fd[2];
	int pid;
	int prev_pfd;

	if (argc < 5)
	{
		ft_printf("\033[31margs must follow the order: [inputfile] [comand1] ... [commandn] [outputfile]\033[0m\n");
		return (1);
	}
	fd_in = opener(argv[1]);
	fd_out = opener(argv[4]);
	cmd_i = 2;
	// unterstuetze auch den fall wenn kein inputfile existiert infile cat wc-l +> 0
	//ft_printf("%i %i\n", fd_in, fd_out);
	if (fd_in >= 0 && fd_out >= 1)
	{
		prev_pfd = fd_in;
		while (cmd_i < (argc - 1))
		{
			if (pipe(fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			pid = fork();
			if (pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (pid == 0)
			{
				dup2(prev_pfd, STDIN_FILENO);
				if(cmd_i < argc - 2)
					dup2(fd[1], STDOUT_FILENO);
				else
					dup2(fd_out, STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				if(execve(ft_exc_path(retrieve_bsc_command(argv[cmd_i], "", ""), envp), ft_exc_args(argv[cmd_i], retrieve_bsc_command(argv[cmd_i], "", "")), envp) == -1)
				{
					perror("execve");
					return (EXIT_FAILURE);
				}
				return (EXIT_SUCCESS);
		
			}
			close(fd[1]);
			if (prev_pfd != fd_in)
				close(prev_pfd);
			prev_pfd = fd[0];
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