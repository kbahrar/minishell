/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/09 18:09:32 by kbahrar           #+#    #+#             */
/*   Updated: 2019/08/09 18:11:18 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minish.h"

void	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (!args[i])
	{
		ft_putchar('\n');
		return ;
	}
	if (ft_strcmp(args[i], "-n") == 0)
		i++;
	while (args[i])
	{
		ft_putstr(args[i]);
		i++;
		if (args[i])
			ft_putchar(' ');
	}
	if (ft_strcmp(args[1], "-n") != 0)
		ft_putchar('\n');
}
