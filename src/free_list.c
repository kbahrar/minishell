/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:19:46 by kbahrar           #+#    #+#             */
/*   Updated: 2019/09/14 21:04:55 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	free_alias(t_alias **alias)
{
	t_alias	*tmp;

	tmp = *alias;
	while (tmp)
	{
		*alias = (*alias)->next;
		free(tmp->cmd);
		free(tmp->valeur);
		free(tmp);
		tmp = NULL;
		tmp = *alias;
	}
}

void		free_paths(char **paths)
{
	int i;

	i = 0;
	while (paths[i])
	{
		if (paths[i])
			free(paths[i]);
		i++;
	}
	free(paths);
}

void		free_sh(char **env, char **args, t_vars **vars)
{
	if (env)
		free_paths(env);
	if (args)
		free_paths(args);
	if (vars)
	{
		free_alias(&g_alias);
		free_list(vars);
	}
}

void		free_list(t_vars **vars)
{
	t_vars	*tmp;

	tmp = *vars;
	while (tmp)
	{
		*vars = (*vars)->next;
		if (tmp->nom)
			free(tmp->nom);
		if (tmp->valeur)
			free(tmp->valeur);
		if (tmp)
			free(tmp);
		tmp = *vars;
	}
}
