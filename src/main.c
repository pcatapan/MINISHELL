/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 19:10:14 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 05:33:27 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_loop(t_main *main)
{
	char	*tmp;

	tmp = getenv("HOME");
	main->files_pwd = ft_strjoin(tmp, "/");
	main->token = (t_token *)malloc(sizeof(t_token));
	if (!main->token)
		return ;
	ft_prompt(main);
	free(main->token);
	free(main->files_pwd);
}

int	main(int argc, char **argv, char **envp)
{
	t_main	*main;

	(void)argc;
	(void)argv;
	g_exit = 0;
	main = (t_main *)malloc(sizeof(t_main));
	if (!main)
		return (0);
	main->copy_env = ft_init_envp(envp);
	main->export_env = malloc (sizeof(char **) * 1);
	if (!main->export_env)
	{
		ft_free_matrix(main->copy_env);
		return (0);
	}
	main->export_env[0] = NULL;
	signal(SIGINT, ft_sig_handel);
	signal(SIGQUIT, ft_sig_handel);
	while (1)
		ft_loop(main);
	ft_free_matrix(main->copy_env);
}
