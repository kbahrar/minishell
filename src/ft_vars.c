/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:49:14 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/04 17:49:27 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static char	*make_nom(char *str)
{
	char	*nom;
	int		i;

	i = 0;
	while (str[i] != '=')
		i++;
	if (!(nom = (char*)malloc(sizeof(char) * i + 1)))
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i] != '=')
	{
		nom[i] = str[i];
		i++;
	}
	nom[i] = '\0';
	return (nom);
}

static char	*make_val(char *str)
{
	char	*val;
	int		i;
	int		j;
	int		t;

	i = 0;
	t = 0;
	while (str[i] != '=')
		i++;
	j = i + 1;
	while (str[i++])
		t++;
	if (!(val = (char*)malloc(sizeof(char) * t)))
		exit(EXIT_FAILURE);
	i = 0;
	while (str[j])
		val[i++] = str[j++];
	val[i] = '\0';
	return (val);
}

t_vars		*init_vars(char **env)
{
	t_vars	*vars;

	if (!(vars = (t_vars*)malloc(sizeof(t_vars))))
		exit(EXIT_FAILURE);
	vars->nom = make_nom(env[0]);
	vars->valeur = make_val(env[0]);
	vars->next = NULL;
	return (vars);
}

t_vars		*ft_vars(char **env)
{
	int		i;
	t_vars	*vars;
	t_vars	*head;

	i = 1;
	head = init_vars(env);
	vars = head;
	while (env[i])
	{
		vars->next = (t_vars*)malloc(sizeof(t_vars));
		vars = vars->next;
		vars->nom = make_nom(env[i]);
		vars->valeur = make_val(env[i]);
		i++;
	}
	vars->next = NULL;
	return (head);
}
