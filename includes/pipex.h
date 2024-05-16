/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:43:52 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/16 18:01:27 by jeberle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <errno.h>
# include "./../libft/libft.h"

char	**ft_exc_args_awk(char *full_cmd);
char	*ft_get_envline(char *needle, char **envp);
char	*ft_exc_path(char *exc, char **envp);
char	*retrieve_bsc_command(char *full_cmd, char *prefix, char *suffix);
char	**ft_exc_args(char *full_cmd, char *command);
int		ft_execve(char *command, char **envp);
#endif