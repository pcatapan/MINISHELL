/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:31:46 by fgrossi           #+#    #+#             */
/*   Updated: 2022/02/22 12:19:09 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>

int				ft_printf(const char *str, ...);
int				ft_putstr_v2(char *str);
int				ft_putnbr(int n);
int				ft_put_unsigned(unsigned int n);
int				ft_putchar(int c);

#endif
