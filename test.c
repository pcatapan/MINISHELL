/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:04:57 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/29 19:29:48 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

int	main(int argv, char **argc, char **envp)
{
	char	**one;

	one = malloc(sizeof(char **) * 2);
	one[0] = "pwd";
	one[1] = "Messaggio";
	if (execve("pwd", one, envp))
		perror("TEST");
}
