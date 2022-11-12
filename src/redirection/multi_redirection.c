/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:36:58 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/12 19:51:51 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

char	*ft_create_line(t_token *token)
{
	char	*tmp;
	char	*val;
	int		i;

	if (!(tmp = (char *)malloc(sizeof(char) * 1)))
		return (NULL);
	i = 0;
	tmp = "\0";
	while (token->value[i])
	{
		val = ft_strjoin(token->value[i], " ");
		tmp = ft_strjoin(tmp, val);
		free(val);
		i++;
	}
	return (tmp);
}

void	ft_execute_multi_redir(t_token *token)
{
	char	*line;
	// char	**matrix;
	// int		i;
	// int		input;
	// int		ouput;

	// ft_print_lst(token);
	line = ft_create_line(token);
	printf("%s\n", line);
	// matrix = ft_split_original(line, 127);
	// ft_set_info(matrix, main, main->copy_line, 1);
	// ft_print_lst(main->token);
	// while (main->token)
	// {
	// 	if (main->token->command == NULL || ft_strcmp(main->token->command, "bin/file"))
	// 		input = open(main->token->value[0], O_CREAT | O_RDWR, 0644);
	// 	main->token = main->token->next;
	// }
}
