/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:34:12 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/22 15:34:26 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

void	wait_handling(int argc, char **argv, int processes[])
{
	int	i;

	i = 0;
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		while (i < argc - 4)
		{
			waitpid(processes[i], NULL, 0);
			i++;
		}
	}
	else
	{
		while (i < argc - 3)
		{
			waitpid(processes[i], NULL, 0);
			i++;
		}
	}
}

void	handle_error(const char *message)
{
	ft_putstr_fd(STDERR_FILENO, (char *)message);
	exit(EXIT_FAILURE);
}
