/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/15 14:40:22 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/15 14:40:35 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	*error_var(char *tmp, char *tmp1, int flag)
{
	if (flag == 0)
		ft_putstr_fd("Illegal variable name.\n", 2);
	else
	{
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": Undifined variable.\n", 2);
		free(tmp);
		free(tmp1);
	}
	return (NULL);
}

static char	*var_value(char **str, int *i)
{
	char	*value;
	int		j;

	value = ft_strnew(4096);
	j = *i;
	(*str)++;
	while ((*str)[j])
	{
		if (ft_isalnum((*str)[j]) == 0)
		{
			(*i) = j;
			return (value);
		}
		value[j] = (*str)[j];
		j++;
	}
	(*i) = j;
	return (value);
}

static char	*recrusivete(char **var, char **af, t_vars *vars)
{
	char	*value;
	char	*after;
	int		i;
	int		j;

	i = 0;
	value = var_value(var, &i);
	after = ft_strnew(4096);
	j = 0;
	while ((*var)[i])
	{
		if ((*var)[i] == '$')
		{
			if (!(*af = var_dol(ft_strchr(*var, '$'), vars)))
			{
				free(after);
				free(value);
				return (NULL);
			}
			(*var)[i] = '\0';
		}
		after[j++] = (*var)[i++];
	}
	*var = value;
	return (after);
}

static char	*ft_join(char *value, char *after, char *var)
{
	char	*tmp;
	int		i;

	i = 0;
	if (after)
	{
		tmp = ft_strjoin(value, after);
		free(after);
	}
	else
		tmp = ft_strdup(value);
	free(value);
	if (var[0] != '$')
	{
		while (var[i])
		{
			if (var[i] == '$')
				var[i] = '\0';
			i++;
		}
		value = ft_strjoin(var, tmp);
		free(tmp);
		tmp = value;
	}
	return (tmp);
}

char		*var_dol(char *var, t_vars *vars)
{
	char	*value;
	char	*after;
	char	*tmp;
	char	*tmp1;

	after = NULL;
	tmp = ft_strchr(var, '$');
	if (ft_isalpha(tmp[1]) == 0)
		return (error_var(NULL, after, 0));
	if (!(tmp1 = recrusivete(&tmp, &after, vars)))
		return (NULL);
	while (vars)
	{
		if (ft_strcmp(vars->nom, tmp) == 0)
		{
			value = ft_strjoin(vars->valeur, tmp1);
			free(tmp);
			free(tmp1);
			value = ft_join(value, after, var);
			return (value);
		}
		vars = vars->next;
	}
	return (error_var(tmp, tmp1, 1));
}
