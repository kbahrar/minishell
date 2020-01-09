/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:33:36 by kbahrar           #+#    #+#             */
/*   Updated: 2019/07/23 19:34:37 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

char	**my_paths(char **env)
{
	int		i;
	char	**tab;

	i = 0;
	tab = NULL;
	while (env[i])
	{
		if (ft_strstr(env[i], "PATH=") != NULL)
			tab = ft_strsplit(ft_strstr(env[i], "/"), ':');
		i++;
	}
	return (tab);
}

char	*access_file(char **env, char *file)
{
	int		i;
	char	*tmp;
	char	**paths;

	i = 0;
	if ((file[0] == '.' && file[1] == '/') ||
	!(paths = my_paths(env)))
		return (file);
	while (paths[i])
	{
		tmp = ft_pathjoin(paths[i], file);
		if (access(tmp, F_OK) == 0)
		{
			free(file);
			free_paths(paths);
			return (tmp);
		}
		free(tmp);
		i++;
	}
	free_paths(paths);
	return (file);
}
