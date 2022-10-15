/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnumber.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 19:23:20 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/28 01:45:02 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	ft_digit(long nb)
{
	int	n;

	if (nb < 0)
	{
		nb = nb * -1;
		write (1, "-", 1);
	}
	if (nb >= 10)
	{
		ft_digit(nb / 10);
		n = (nb % 10) + 48;
		write (1, &n, 1);
	}
	if (nb >= 0 && nb < 10)
	{
		n = nb + 48;
		write (1, &n, 1);
	}
}

static int	ft_len(long nb)
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

int	ft_putnumber(int num)
{
	int		count;
	long	nb;

	nb = num;
	count = ft_len(nb);
	ft_digit(nb);
	return (count);
}
