/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:15:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/10/26 18:08:51 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_output_redirect(t_token *token, t_main *main)
{
	int	fd;

	token->dup = dup(STDOUT_FILENO);
	if (token->output == 1)
	{
		fd = open (token->name_file, O_CREAT | O_RDWR, 0644);
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
	token->stdoutput = fd;
}

void	ft_input_redirect(t_token *token, t_main *main)
{
	int	fd;

	token->dup = dup(STDIN_FILENO);
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
	token->stdinput = fd;
}

t_token	*ft_redirections(t_token *token, t_main *main)
{
	pid_t	pidchild;

	pidchild = fork();
	if (pidchild != 0)
		waitpid(pidchild, 0, 0);
	else
	{
		if (token->output == 1 || token->append == 1)
			ft_output_redirect(token, main);
		if (token->input == 1 || token->heredoc == 1)
			ft_input_redirect(token, main);
		free(token->value[1]);
		free(token->value[2]);
		token->value[1] = NULL;
		ft_qualcosa(token);
	}
	main->redirections = false;
	if (token->stdoutput != STDOUT_FILENO)
		dup2(token->dup, STDOUT_FILENO);
	else if (token->stdinput != STDIN_FILENO)
		dup2(token->dup, STDIN_FILENO);
	if (token->next)
		token = token->next;
	return (token);
}
