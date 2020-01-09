/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:39:54 by kbahrar           #+#    #+#             */
/*   Updated: 2019/09/14 23:58:46 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	**free_null(char **tab, char *line, char *cpy)
{
	if (tab)
		free_paths(tab);
	if (line)
		free(line);
	if (cpy)
		free(cpy);
	return (NULL);
}

static int	dolchr(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}

static int	modifier_tab(char **tab, char **env, t_vars *vars)
{
	int		i;
	char	*tmp;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '~' || dolchr(tab[i]) == 1)
		{
			if (tab[i][0] == '~')
				tmp = home_path(tab[i], env);
			if (dolchr(tab[i]) == 1)
				tmp = var_dol(tab[i], vars);
			if (tmp)
			{
				free(tab[i]);
				tab[i] = ft_strdup(tmp);
				free(tmp);
			}
			else
				return (-1);
		}
		i++;
	}
	return (0);
}

char		**last_modifier(char **tab, t_alias *alias)
{
	char	**cmd_al;
	char	**ret;

	while (alias)
	{
		if (ft_strcmp(alias->cmd, tab[0]) == 0)
		{
			cmd_al = ft_strsplit(alias->valeur, ' ');
			ret = ft_tabjoin(cmd_al, tab, 1);
			free_sh(tab, cmd_al, NULL);
			return (ret);
		}
		alias = alias->next;
	}
	return (tab);
}

char		**read_line(char **env, t_vars *vars)
{
	char	*line;
	char	**tab;
	char	*cpy;

	line = NULL;
	if (get_next_line(0, &line) == -1)
		return (free_null(NULL, line, NULL));
	cpy = ft_strtrim(line);
	if (cpy[0] == '\0')
		return (free_null(NULL, line, cpy));
	free(line);
	if (!(tab = sh_split(cpy)))
		return (free_null(NULL, NULL, cpy));
	free(cpy);
	if (modifier_tab(tab, env, vars) == -1)
		return (free_null(tab, NULL, NULL));
	tab = last_modifier(tab, g_alias);
	return (tab);
}
