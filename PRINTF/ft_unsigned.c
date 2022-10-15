/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 21:54:08 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/28 08:10:20 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_digitunsi(unsigned int nb)
{
	int	n;

	if (nb >= 10)
	{
		ft_digitunsi(nb / 10);
		n = (nb % 10) + 48;
		write (1, &n, 1);
	}
	if (nb >= 0 && nb < 10)
	{
		n = nb + 48;
		write (1, &n, 1);
	}
}

unsigned int	ft_lenunsi(unsigned int nb)
{
	int	i;

	i = 0;
	if (nb == 0)
		i++;
	if (nb < 0)
	{
		nb = nb * -1;
		i++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

int	ft_unsigned(unsigned int num)
{
	int	count;

	count = ft_lenunsi(num);
	ft_digitunsi(num);
	return (count);
}
