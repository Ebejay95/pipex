/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeberle <jeberle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:47:51 by jeberle           #+#    #+#             */
/*   Updated: 2024/05/17 03:08:43 by jeberle          ###   ########.fr       */
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
	if (!pathline)
		return (NULL);
	pathcount = ft_count_words(pathline, ':');
	paths = ft_split(pathline, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (i < pathcount)
	{
		joined = ft_strjoin(paths[i], "/");
		if (joined == NULL)
		{
			ft_array_l_free(paths, pathcount);
			return (NULL);
		}
		joined = ft_strjoin(joined, exc);
		if (joined == NULL)
		{
			ft_array_l_free(paths, pathcount);
			return (NULL);
		}
		if (access(joined, X_OK) == 0)
		{
			ft_array_l_free(paths, pathcount);
			return (joined);
		}
		free(joined);
		i++;
	}
	ft_array_l_free(paths, pathcount);
	return (NULL);
}
