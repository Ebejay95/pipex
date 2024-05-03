/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/03 16:56:36 by jeberle          ###   ########.fr       */
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

int	main (void)
{
	int id;
	int status;
	int fd[2];
	pipe(fd);
	id = fork();
	if(id == 0)
	{
		close(fd[0]);
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		write(fd[1], &x, sizeof(int));
		close(fd[1]);
	}
	else
	{
		int y;
		close(fd[1]);
		wait(&status);
		read(fd[0], &y, sizeof(int));
		close(fd[1]);
		printf("U entered number: %i\n", y);
	}
	return (0);
}



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





//ft_printf("\nWEXIT:%i WIFEXIT:%i", WEXITSTATUS(status), WIFEXITED(status));