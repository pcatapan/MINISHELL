/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/07 14:14:07 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;
//	t_token	*token;

	(void)argc;
	(void)argv;
	main = malloc(sizeof(t_main));
//	token = malloc(sizeof(t_token));
	if (!main)
		return (0);
	main->copy_env = ft_init_envp(envp);
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
		ft_prompt(main->copy_env, main);
	ft_free_matrix(main->copy_env);
	free(main);
}
