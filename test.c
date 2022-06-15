/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:04:57 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/15 12:40:13 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include <termcap.h>
#include <stdlib.h>
#include <curses.h>
int putchar(int tc)
{
	write(1, &tc, 1);
	return (0);
}
 
int	main(void)
{
	char *env = getenv("TERM");
	if (env == NULL)
		env = "xterm";

	tgetent(NULL, env); 
	char *cm = tgetstr("cm", NULL);

	tputs(tgoto(cm, 5, 5), 1, putchar);
}
