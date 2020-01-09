/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 17:29:31 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/05 17:30:12 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	ignore(char *line, int *i)
{
	if (line[*i] == '\'')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
		if (line[*i] == '\0')
			return (-1);
	}
	else if (line[*i] == '"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '"')
			(*i)++;
		if (line[*i] == '\0')
			return (-2);
	}
	return (0);
}

static int	how_words(char *line)
{
	int		total;
	int		i;
	int		g;

	i = 0;
	total = 1;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			while (line[i] && (line[i] == ' ' || line[i] == '\t'))
				i++;
			if (line[i] != '\0')
				total++;
		}
		if (line[i] == '\'' || line[i] == '"')
		{
			g = ignore(line, &i);
			if (g < 0)
				return (g);
		}
		i++;
	}
	return (total);
}

static int	how_char(char *line, int i)
{
	int		total;
	char	c;

	total = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '"')
		{
			c = line[i];
			i++;
			while (line[i] && line[i] != c)
			{
				i++;
				total++;
			}
		}
		if (line[i] == ' ' || line[i] == '\t')
			return (total);
		i++;
		total++;
	}
	return (total);
}

static char	*remplir_tab(char *str, int *place)
{
	char	*cpy;
	int		i;
	char	c;

	i = 0;
	if (!(cpy = (char*)malloc(sizeof(char) * how_char(str, *place) + 1)))
		exit(EXIT_FAILURE);
	while (str[*place] && str[*place] != ' ' && str[*place] != '\t')
	{
		if (str[*place] == '\'' || str[*place] == '"')
		{
			c = str[*place];
			(*place)++;
			while (str[*place] && str[*place] != c)
				cpy[i++] = str[(*place)++];
			(*place)++;
		}
		else
			cpy[i++] = str[(*place)++];
	}
	cpy[i] = '\0';
	return (cpy);
}

char		**sh_split(char *line)
{
	int		w;
	char	**tab;
	int		i;

	i = 0;
	if ((w = how_words(line)) < 0)
	{
		if (w == -1)
			ft_putendl_fd("Unmatched '.", 2);
		else
			ft_putendl_fd("Unmatched \".", 2);
		return (NULL);
	}
	if (!(tab = (char**)malloc(sizeof(char*) * (w + 1))))
		exit(EXIT_FAILURE);
	tab[w] = NULL;
	w = 0;
	while (line[i])
	{
		tab[w++] = remplir_tab(line, &i);
		while (line[i] && (line[i] == ' ' || line[i] == '\t'))
			i++;
	}
	return (tab);
}
