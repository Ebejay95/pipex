/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:52 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/17 07:40:46 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include "./../libft/libft.h"
# define MAX_BYTES 8000

char	*check_and_extract_quotes(const char* input);
char	**ft_exc_args_awk(char *full_cmd, char **envp);
char	*ft_get_envline(char *needle, char **envp);
char	*ft_exc_path(char *exc, char **envp);
char	*retrieve_bsc_command(char *full_cmd, char *prefix, char *suffix);
char	**ft_exc_args(char *full_cmd, char *command, char **envp);
int		ft_execve(char *command, char **envp);
#endif