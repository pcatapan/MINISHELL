/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 03:50:37 by fgrossi           #+#    #+#             */
/*   Updated: 2022/10/16 15:56:21 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr_v2(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (write(1, "(null)", 6));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_put_unsigned(unsigned int n)
{
	int	t;

	t = 0;
	if (n > 9)
		t += ft_putnbr(n / 10);
		t += ft_putchar(n % 10 + '0');
	return (t);
}

int	ft_putnbr(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
	{
		count += ft_putnbr(n / 10);
		count += ft_putchar('8');
	}
	else if (n < 0)
	{
		count += ft_putchar('-');
		count += ft_putnbr(-n);
	}
	else
	{
		if (n > 9)
		{
			count += ft_putnbr(n / 10);
		}
		count += ft_putchar(48 + n % 10);
	}
	return (count);
}
