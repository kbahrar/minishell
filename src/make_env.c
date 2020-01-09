/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 18:40:38 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/10 18:41:26 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	size_char(t_vars *vars)
{
	int	i;
	int tot;

	i = 0;
	tot = 1;
	while (vars->nom[i++])
		tot++;
	i = 0;
	while (vars->valeur[i++])
		tot++;
	return (tot);
}

static int	size_var(t_vars *vars)
{
	int	tot;

	tot = 0;
	while (vars)
	{
		vars = vars->next;
		tot++;
	}
	return (tot);
}

char		**make_env(t_vars *tmp)
{
	char	**env;
	int		i;
	int		j;
	int		k;

	if (!(env = (char**)malloc(sizeof(char*) * (size_var(tmp) + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (tmp)
	{
		j = 0;
		k = 0;
		env[i] = (char*)malloc(sizeof(char) * size_char(tmp) + 2);
		while (tmp->nom[j])
			env[i][k++] = tmp->nom[j++];
		env[i][k++] = '=';
		j = 0;
		while (tmp->valeur[j])
			env[i][k++] = tmp->valeur[j++];
		env[i][k] = '\0';
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}
