/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:52 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/20 07:18:37 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "./../libft/libft.h"
# define MAX_BYTES 8000

char	*ft_get_envline(char *needle, char **envp);
char	*ft_exc_path(char *exc, char **envp);
char	*retrieve_bsc_command(char *full_cmd, char *prefix, char *suffix);
char	**ft_exc_args(char *full_cmd);
int		ft_execve(char *command, char **envp);
#endif