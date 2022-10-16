/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:15:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/16 15:15:02 by fgrossi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_output_redirect(t_token *token, t_main *main)
{
	int	fd;

	if (token->output == 1)
	{
		fd = open (token->name_file, O_CREAT | O_RDWR | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (token->append == 1)
	{
		fd = open (token->name_file, O_CREAT | O_RDWR | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		exit(0);
	}
}

void	ft_input_redirect(t_token *token, t_main *main)
{
	int	fd;

	if (token->input == 1)
	{
		fd = open (token->name_file, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		if (fd == -1)
		{
			perror(RED ERROR_FILE COLOR_RES);
			write(fd, "1", 1);
			exit(0);
		}
	}
	else if (token->heredoc == 1)
	{	
		if (ft_heredoc(token, main) == -1)
		{
			perror(RED ERROR_FILE COLOR_RES);
			write(fd, "1", 1);
			exit(0);
		}	
	}
}

void	ft_redirections(t_token *token, t_main *main)
{
	pid_t	pidchild;

	pidchild = fork();
// <<<<<<< HEAD:src/redirections.c
// 	// Qui il processo che gesticse le esecuzioni si ferma
// 	// La chiusura della write è irreversibile
// =======
// >>>>>>> 3b443c0100100717225c5d3263a325ac0ae6683e:src/redirection/redirections.c
	if (pidchild != 0)
		waitpid(pidchild, 0, 0);
	while (token && pidchild == 0)
	{
		if (token->output == 1 || token->append == 1)
			ft_output_redirect(token, main);
		if (token->input == 1 || token->heredoc == 1)
			ft_input_redirect(token, main);
		token = token->next;
	}
	main->redirections = false;
	// ft_funzione_da_creare();
}
