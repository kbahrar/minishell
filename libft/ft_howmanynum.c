/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_howmanynum.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbahrar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:02:49 by kbahrar           #+#    #+#             */
/*   Updated: 2019/07/11 16:05:32 by kbahrar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_howmanynum(long long int num)
{
	int	i;

	i = 1;
	while (num >= 10)
	{
		num = num / 10;
		i++;
	}
	return (i);
}
