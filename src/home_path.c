/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 14:06:29 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/15 14:07:06 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	*error_path(char *h_path)
{
	ft_putstr_fd(h_path, 2);
	ft_putstr_fd(": Unknown user.\n", 2);
	free(h_path);
	return (NULL);
}

static char	*mod_path(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '/')
		{
			str[i + 1] = '\0';
			break ;
		}
		i++;
	}
	return (str);
}

char		*home_path(char *path, char **env)
{
	char	*cpy;
	char	*h_path;
	int		i;

	i = 0;
	cpy = NULL;
	path++;
	while (env[i])
	{
		if (ft_strstr(env[i], "HOME=") != NULL)
			cpy = ft_strdup(ft_strchr(env[i], '/'));
		i++;
	}
	if (!cpy)
		return (NULL);
	if (path[0] != '\0' && path[0] != '/')
		cpy = mod_path(cpy);
	h_path = ft_strnew(4096);
	ft_strcpy(h_path, cpy);
	ft_strcat(h_path, path);
	free(cpy);
	if (access(h_path, F_OK) != 0 && (path[0] != '\0' && path[0] != '/'))
		return (error_path(h_path));
	return (h_path);
}
