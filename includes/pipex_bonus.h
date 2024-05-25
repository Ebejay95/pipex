/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:40:14 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/25 22:40:25 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include "./../libft/libft.h"

typedef struct s_args
{
	int		i;
	int		c;
	char	**v;
}	t_args;

typedef struct s_fds
{
	int		in;
	int		out;
	int		tube[2];
	int		prevpipe;
}	t_fds;

typedef struct s_processes
{
	int	current;
	int	track[1024];
}	t_processes;

int		save_hd_input(char **argv);
int		prcss_cmmnds(t_args *args, t_fds *fds, t_processes *prcs, char **envp);
int		clear_end(t_args *a, t_fds *fds);
int		initialize(t_args *args, t_fds *fds, int argc, char **argv);
int		open_in_out(t_args *a, t_fds *fds);
char	*ft_get_envline(char *needle, char **envp);
char	*ft_exc_path(char *exc, char **envp);
char	*retrieve_bsc_command(char *full_cmd, char *prefix, char *suffix);
char	**ft_exc_args(char *full_cmd, int *arglen);
int		ft_execve(char *command, char **envp);
int		wait_handling(t_args *args, t_processes *prcs);
int		child_process(t_fds *fds, t_args *args, char **envp);
void	main_process(t_processes *prcs, t_fds *fds, t_args *args);
void	do_pipe_act(t_processes *prcs, t_fds *fds, t_args *args, char **envp);
int		prepare_piping(t_processes *prcs, t_fds *fds);
#endif