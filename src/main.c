/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/25 21:28:54 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	main = (t_main *)malloc(sizeof(t_main) * 1);
	main->token = (t_token *)malloc(sizeof(t_token));
	if (!main || !main->token)
		return (0);
	main->copy_env = ft_init_envp(envp);
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
		ft_prompt(main->copy_env, main);
	ft_free_main(main);
}
