/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:18:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/28 09:04:50 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		write (1, "(null)", 6);
		return (6);
	}	
	while (str[i] != '\0')
	{
		write (1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	var;

	i = 0;
	count = 0;
	va_start(var, str);	
	while(str[i] != '%')
		count += ft_char(str[i++]);
	while (str[i] != '%')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == 's')
			count += ft_write(va_arg(var, char *));
		else if (str[i] == 'c')
			count += ft_char(va_arg(var, int));
		else if (str[i] == 'p')
			count += ft_putesa(va_arg(var, uintptr_t));
		else if (str[i] == 'd' || str[i] == 'i')
			count += ft_putnumber(va_arg(var,int));
		else if (str[i] == 'u')
			count += ft_unsigned(va_arg(var,unsigned int));
		else if (str[i] == 'x' || str[i] == 'X')
			count += ft_esadecimal(va_arg(var, unsigned int), str[i]);
		else if (str[i] == '%' && str[i + 1] == '%')
		{
			write(1, "%%", 1);
			count++;
			i++;
		}
		else if (str[i] != '%')
		{
			write (1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(var);
	return (count);
}


// int main()
// {
// 	int ret;
 	
//  	ret = 5;
//   	ft_printf("%d",ft_printf(" %% "));
//   	//printf("\n\n");
//   	printf("%d", printf(" %% "));
//  }

