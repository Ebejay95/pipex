/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonathaneberle <jonathaneberle@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 22:10:10 by jonathanebe       #+#    #+#             */
/*   Updated: 2024/05/25 22:25:15 by jonathanebe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/pipex_bonus.h"

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
	ft_array_l_free(paths, pathcount);
	return (NULL);
}
