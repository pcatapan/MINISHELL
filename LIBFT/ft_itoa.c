/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:31:35 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/23 21:39:42 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/**
 * @brief Write the number in str for compleat the conversion
 * 
 * @param str	Where write the number
 * @param nb	Copy of number
 * @param len	Length of number
 * @param n		Original number
 * 
 * @return void* 
 */
static	void	*ft_digit(char *str, long nb, size_t len, int n)
{
	size_t	s;

	s = 0;
	if (nb < 0)
	{
		s = -1;
		nb = nb * -1;
		str[0] = '-';
	}
	str[len] = '\0';
	if (n == 0)
	{
		str[len - 1] = '0';
		return (str);
	}
	while (nb > 0)
	{
		str[--len] = (nb % 10) + 48;
		nb = nb / 10;
	}
	return (*(&str));
}

/**
 * @brief Search the length of number
 * 
 * @param nb Numbert of to search length
 * 
 * @return int is the length
 */
static int	ft_len_num(long nb)
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

/**
 * @brief Convert the int in string
 * 
 * @param n in the to convert
 * 
 * @return char* 
 */
char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	long	nb;

	nb = n;
	len = ft_len_num(nb);
	str = (char *)malloc(sizeof (char) * len + 1);
	if (!str)
		return (NULL);
	return (ft_digit(str, nb, len, n));
}
