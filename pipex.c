/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:03 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/25 22:26:14 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

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
	if (clear_end(&fds) != 0)
		return (1);
	exit_code = wait_handling(&args, &prcs);
	return (exit_code);
}
