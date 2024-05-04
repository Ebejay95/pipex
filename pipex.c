/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/04 09:31:37 by jonathanebe      ###   ########.fr       */
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
		ft_strcpy(tmp, filecontent);
		ft_strcat(tmp, line);
		free(filecontent);
		tmp = filecontent;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (filecontent);
}

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
int	validate_args(int argc)
{
	//char *input;
	//char *output;
	//char *command1;
	//char *command2;


	if (argc != 5)
	{
		ft_printf("args must follow the order: [inputfile] [comand1] [command2] [outputfile]\n");
		return (1);
	}
	//input = argv[1];
	//output = argv[2];
	//command1 = argv[3];
	//command2 = argv[4];
	return (0);
}

void	perform_pipex(char **argv)
{
	char *input;
	char *output;
	char *command1;
	char *command2;

	input = argv[1];
	output = argv[2];
	command1 = argv[3];
	command2 = argv[4];
	ft_printf("PIPEX:\n");
	ft_printf("\tinput: %s\n", get_file_content(input));
	ft_printf("\toutput: %s\n", output);
	ft_printf("\tcommand1: %s\n", command1);
	ft_printf("\tcommand2: %s\n", command2);
}

int main(int argc, char **argv)
{
	if(validate_args(argc) == 1)
		return (0);
	perform_pipex(argv);
	return (0);
}




//ft_printf("\nWEXIT:%i WIFEXIT:%i", WEXITSTATUS(status), WIFEXITED(status));