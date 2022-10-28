/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 19:10:04 by pcatapan          #+#    #+#             */
/*   Updated: 2022/10/15 20:02:01 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_echo(t_token *token, int fd[2])
{
	int	i;

	i = 1;
	if (ft_strcmp(token->value[1], "-n") != 0)
		i++;
	while (token->value[i])
	{
		printf("%s", ft_clear_value(token->value[i]));
		if (token->value[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(token->value[1], "-n") == 0)
		printf("\n");
}
