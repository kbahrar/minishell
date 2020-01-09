/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 21:47:04 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/07 17:11:35 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	free_elem(t_vars **vars)
{
	free((*vars)->nom);
	free((*vars)->valeur);
	free(*vars);
}

void	ft_del_elem(char *nom, t_vars **vars)
{
	t_vars	*tmp;
	t_vars	*pre;

	tmp = (*vars)->next;
	pre = *vars;
	if (ft_strcmp(pre->nom, nom) == 0)
	{
		*vars = tmp;
		free_elem(&pre);
	}
	else
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->nom, nom) == 0)
			{
				pre->next = tmp->next;
				free_elem(&tmp);
				return ;
			}
			tmp = tmp->next;
			pre = pre->next;
		}
	}
}

void	ft_unsetenv(char **args, t_vars **vars)
{
	int		i;

	i = 1;
	if (args[i] == NULL)
		ft_putendl_fd("unsetenv: Too few arguments.", 2);
	else
	{
		while (args[i])
		{
			ft_del_elem(args[i], vars);
			i++;
		}
	}
}
