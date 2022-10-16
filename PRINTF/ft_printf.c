/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 16:14:55 by fgrossi           #+#    #+#             */
/*   Updated: 2022/10/16 15:56:12 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_digit(uintptr_t nb, char *base)
{
	if (nb < 0)
	{
		ft_putchar('-');
		ft_digit(-nb, base);
	}
	if (nb >= 16)
	{
		ft_digit(nb / 16, base);
		ft_putchar(base[nb % 16]);
	}
	else if (nb >= 0)
	{
		ft_putchar(base[nb % 16]);
	}
}

int	ft_len(uintptr_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

unsigned int	ft_puthex(uintptr_t num, char lett)
{
	int		count;
	char	*base;

	count = ft_len(num);
	if (lett == 'p')
	{
		write(1, "0x", 2);
		count += 2;
		base = "0123456789abcdef";
		ft_digit(num, base);
	}
	else if (lett == 'X')
	{
		base = "0123456789ABCDEF";
		ft_digit(num, base);
	}
	else
	{
		base = "0123456789abcdef";
		ft_digit(num, base);
	}
	return (count);
}

int	ft_formats(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (format == 's')
		count += ft_putstr_v2(va_arg(args, char *));
	else if (format == 'p')
		count += ft_puthex(va_arg(args, uintptr_t), format);
	else if (format == 'd' || format == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (format == 'u')
		count += ft_put_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_puthex(va_arg(args, unsigned int), format);
	else if (format == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	va_list	args;
	int		count;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_formats(args, str[i + 1]);
			i++;
		}
		else
			count += ft_putchar(str[i]);
		i++;
	}
	va_end(args);
	return (count);
}
