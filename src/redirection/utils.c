/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 03:26:32 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 03:14:15 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_single_redir(t_token *token, t_main *main)
{
	if (token->heredoc == 1)
		ft_heredoc(token, main);
	if (token->output == 1 || token->append == 1)
		ft_output_redirect(token, main);
	if (token->input == 1)
		ft_input_redirect(token);
	ft_delete_redirection(token);
	if (token->command == NULL)
	{
		if (token->stdoutput != STDOUT_FILENO)
			dup2(token->dup, STDOUT_FILENO);
		else if (token->stdinput != STDIN_FILENO)
			dup2(token->dup, STDIN_FILENO);
	}
	ft_qualcosa(token, main);
}

char	*ft_create_line(t_token *token)
{
	char	*rtr;
	char	*tmp;
	char	*val;
	int		i;

	rtr = (char *)malloc(sizeof(char) * 1);
	if (!rtr)
		return (NULL);
	i = 0;
	tmp = "\0";
	while (token->value[i])
	{
		val = ft_strjoin(token->value[i], " ");
		rtr = ft_strjoin(tmp, val);
		free(val);
		tmp = ft_strdup(rtr);
		i++;
	}
	free(tmp);
	printf("%s\n", rtr);
	return (rtr);
}

char	*ft_set_to_del(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
			line[i] = 127;
		i++;
	}
	return (line);
}

char	**ft_clear_matrix(char **matrix)
{
	int		i;
	char	*tmp;

	i = 1;
	while (matrix[i])
	{
		tmp = ft_strdup(matrix[i]);
		free(matrix[i]);
		matrix[i++] = ft_strclear(tmp, 127);
		free(tmp);
	}
	return (matrix);
}

int	ft_count_redir_value(t_token *token)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (token->value[i])
	{
		j = 0;
		while (token->value[i][j])
		{
			if (token->value[i][j] == 62 || token->value[i][j] == 60)
				count++;
			j++;
		}
		if (count > 1)
			break ;
		i++;
	}
	return (count);
}
