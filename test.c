/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:04:57 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/29 04:18:08 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int argv, char **argc, char **envp)
{
	char	**one;

	one = malloc(sizeof(char **) * 2);
	one[0] = "echo";
	one[1] = "Messaggio";
	if (execve("usr/bin/echo", one, envp))
		perror("TEST");
}
