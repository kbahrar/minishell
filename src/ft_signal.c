/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 19:34:54 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/11 19:36:59 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	fun_child(int sign)
{
	if (sign == SIGINT)
	{
		ft_putstr("\n");
		signal(SIGINT, fun_child);
	}
}

void	fun_father(int sign)
{
	if (sign == SIGINT)
	{
		ft_putstr("\n\e[7mkb-sh $>\033[0m ");
		signal(SIGINT, fun_father);
	}
}
