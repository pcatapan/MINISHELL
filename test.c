/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:04:57 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/14 22:18:54 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	char	*d;

	fd = ttyslot();
	if (isatty(fd))
		printf("aaa\n");
	d = ttyname(fd);
	printf("d - %s\n", d);
}
