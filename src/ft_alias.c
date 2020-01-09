/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alias.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/14 23:30:31 by kbahrar           #+#    #+#             */
/*   Updated: 2019/09/14 23:30:33 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

static void	init(t_alias **alias, char *cmd, char *vl)
{
	*alias = (t_alias*)malloc(sizeof(t_alias));
	(*alias)->cmd = ft_strdup(cmd);
	(*alias)->valeur = ft_strdup(vl);
	(*alias)->next = NULL;
}

static void	show_alias(t_alias *al, char *cmd, int flag)
{
	int	flag2;

	flag2 = 1;
	while (al)
	{
		if (cmd)
			if (ft_strcmp(al->cmd, cmd) == 0)
				flag2 = 0;
		if (flag == 0 || flag2 == 0)
		{
			ft_putstr("alias :\t");
			ft_putstr(al->cmd);
			ft_putstr(" = \"");
			ft_putstr(al->valeur);
			ft_putstr("\"\n");
			flag2 = 1;
		}
		al = al->next;
	}
}

static void	add_alias(t_alias **alias, char *cmd, char *vl)
{
	t_alias	*tmp;

	tmp = *alias;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, cmd) == 0)
		{
			free(tmp->valeur);
			tmp->valeur = ft_strdup(vl);
			return ;
		}
		if (tmp->next == NULL)
		{
			tmp->next = (t_alias*)malloc(sizeof(t_alias));
			break ;
		}
		tmp = tmp->next;
	}
	tmp = tmp->next;
	tmp->cmd = ft_strdup(cmd);
	tmp->valeur = ft_strdup(vl);
	tmp->next = NULL;
}

void		ft_alias(t_alias **alias, char *cmd, char *vl)
{
	if (cmd == NULL)
		show_alias(*alias, NULL, 0);
	else if (vl == NULL)
		show_alias(*alias, cmd, 1);
	else
	{
		if (*alias == NULL)
			init(alias, cmd, vl);
		else
			add_alias(alias, cmd, vl);
	}
}
