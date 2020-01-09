/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:03:56 by kbahrar           #+#    #+#             */
/*   Updated: 2019/09/15 22:22:23 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static int	error_hand(int flag)
{
	if (flag == 0)
		ft_putendl_fd("setenv: Too many arguments.", 2);
	else if (flag == 1)
		ft_putendl_fd("setenv: Variable name must begin with a letter.", 2);
	else
	{
		ft_putstr_fd("setenv: Variable name must ", 2);
		ft_putendl_fd("contain alphanumeric characters.", 2);
	}
	return (-1);
}

static int	checking(char **args)
{
	int		i;
	int		check;

	i = 1;
	check = 0;
	while (args[i++])
		check++;
	i = 0;
	if (check > 2)
		return (error_hand(0));
	else if (ft_isalpha(args[1][0]) == 0)
		return (error_hand(1));
	else
	{
		while (args[1][i])
		{
			if (ft_isalnum(args[1][i]) == 0)
				return (error_hand(3));
			i++;
		}
		return (1);
	}
}

static void	new_var(char *nom, char *value, t_vars **tmp)
{
	(*tmp) = (*tmp)->next;
	(*tmp)->nom = ft_strdup(nom);
	if (value)
		(*tmp)->valeur = ft_strdup(value);
	else
		(*tmp)->valeur = ft_strdup("");
	(*tmp)->next = NULL;
}

void		ft_setenv(char **args, t_vars **vars)
{
	t_vars	*tmp;

	tmp = *vars;
	if (checking(args) < 0)
		return ;
	while (tmp)
	{
		if (ft_strcmp(tmp->nom, args[1]) == 0)
		{
			free(tmp->valeur);
			if (args[2])
				tmp->valeur = ft_strdup(args[2]);
			else
				tmp->valeur = ft_strdup("");
			return ;
		}
		if (tmp->next == NULL)
		{
			if (!(tmp->next = (t_vars*)malloc(sizeof(t_vars))))
				exit(EXIT_FAILURE);
			break ;
		}
		tmp = tmp->next;
	}
	new_var(args[1], args[2], &tmp);
}
