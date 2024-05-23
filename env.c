/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:47:51 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/20 06:55:11 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex.h"

char	*ft_exc_path(char *exc, char **envp)
{
	char	*pathline;
	char	*joined;
	char	**paths;
	int		pathcount;
	int		i;

	pathline = ft_get_envline("PATH", envp);
	pathcount = ft_count_words(pathline, ':');
	paths = ft_split(pathline, ':');
	if (pathline != NULL)
	{
		i = 0;
		while (i < pathcount)
		{
			joined = ft_strjoin(paths[i], exc);
			if (joined == NULL)
				break ;
			if (access(joined, X_OK) == 0)
				return (ft_array_l_free(paths, pathcount), joined);
			i++;
			free(joined);
		}
	}
	return (ft_array_l_free(paths, pathcount), NULL);
}
