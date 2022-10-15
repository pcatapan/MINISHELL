/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 16:19:34 by pcatapan          #+#    #+#             */
/*   Updated: 2022/01/28 08:45:03 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <unistd.h>

int				ft_printf(const char *str, ...);
int				ft_char(char lett);
unsigned int	ft_lenunsi(unsigned int num);
int				ft_unsigned(unsigned int num);
unsigned int	ft_esadecimal(unsigned int num, char lett);
int				ft_putnumber(int num);
int				ft_lenesa(uintptr_t nb);
int				ft_putesa(uintptr_t num);

#endif