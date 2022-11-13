/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:15:28 by aanghel           #+#    #+#             */
/*   Updated: 2022/11/13 00:46:42 by aanghel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_output_redirect(t_token *token, t_main *main)
{
	int	fd;

	token->dup = dup(STDOUT_FILENO);
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
	token->stdoutput = fd;
	ft_change_name_file(main, token, '<');
}

void	ft_input_redirect(t_token *token, t_main *main)
{
	int	fd;

	token->dup = dup(STDIN_FILENO);
	fd = open (token->name_file, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	if (fd == -1)
	{
		perror(RED ERROR_FILE COLOR_RES);
		write(fd, "1", 1);
		exit(0);
	}
	token->stdinput = fd;
}

int	ft_count_redirection(t_token *token)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (token->value[i])
	{
		if (ft_strcmp(token->value[i], "<") \
			|| ft_strcmp(token->value[i], "<<") \
			|| ft_strcmp(token->value[i], ">") \
			|| ft_strcmp(token->value[i], ">>"))
			count++;
		i++;
	}
	return (count);
}

void	ft_single_redir(t_token *token, t_main *main)
{
	if (token->heredoc == 1)
		ft_heredoc(token, main);
	if (token->output == 1 || token->append == 1)
		ft_output_redirect(token, main);
	if (token->input == 1)
		ft_input_redirect(token, main);
	ft_delete_redirection(token);
	if (token->command == NULL)
	{
		if (token->stdoutput != STDOUT_FILENO)
			dup2(token->dup, STDOUT_FILENO);
		else if (token->stdinput != STDIN_FILENO)
			dup2(token->dup, STDIN_FILENO);
	}
	ft_qualcosa(token);
}

t_token	*ft_redirections(t_token *token, t_main *main)
{
	pid_t	pidchild;
	char	*line;

	// if (ft_count_redirection(token) != 1)
	// 	ft_execute_multi_redir(token);
	// else
	{
		pidchild = fork();
		if (pidchild != 0)
			waitpid(pidchild, &main->token->res, 0);
		else
			ft_single_redir(token, main);
		if (token->stdoutput != STDOUT_FILENO)
			dup2(token->dup, STDOUT_FILENO);
		else if (token->stdinput != STDIN_FILENO)
			dup2(token->dup, STDIN_FILENO);
	}
	if (token->next)
		token = token->next;
	return (token);
}

void	ft_delete_redirection(t_token *token)
{
	int	i;

	i = 0;
	if (token)
	{
		while (token->value[i])
		{
			if (ft_strcmp(token->value[i], "<") \
				|| ft_strcmp(token->value[i], "<<") \
				|| ft_strcmp(token->value[i], ">") \
				|| ft_strcmp(token->value[i], ">>"))
			{
				free(token->value[i]);
				token->value[i] = NULL;
			}
			i++;
		}
	}
}
