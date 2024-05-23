/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:47:51 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/23 18:35:21 by jeberle          ###   ########.fr       */
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
	ft_array_l_free(paths, pathcount);
	return (NULL);
}
