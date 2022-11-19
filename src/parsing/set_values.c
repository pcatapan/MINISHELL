/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:57:31 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/13 01:41:20 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_divide_line(char *line, t_token *token, t_main *main)
{
	int		i;
	char	**tmp;
	char	*tmp_comand;

	i = -1;
	while (line[++i])
	{
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] == 32 || line[i] == ')')
			line[i] = 127;
	}
	tmp = ft_split_original(line, 127);
	i = 0;
	while (tmp[i])
	{
		token->value[i + 1] = ft_strdup(tmp[i]);
		i++;
	}
	token->value[i + 1] = NULL;
}

int	ft_count_array(char *line, t_main *main)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == 39 || line[i] == 34)
			count++;
		i = ft_check_double_quote(line, main, i);
		i = ft_check_single_quote(line, main, i);
		if (line[i] != 32 && line[i - 1] == 32)
			count++;
		i++;
	}
	return (count);
}

char	*ft_find_path(char *cmd, t_main *main)
{
	char	**paths;
	char	*right_path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strncmp("PATH=", main->copy_env[i], 5))
		i++;
	paths = ft_split(main->copy_env[i] + 5, ":");
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		right_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(right_path, F_OK) == 0)
			return (right_path);
		free(right_path);
		i++;
	}
	ft_free_matrix(paths);
	return (0);
}

/*
Aggiungere funzione per settare priorita, ideale prima dello strudup
prima di passare a path bisogna pulire il paramentro da eventuali '('
come chiuderla?
*/
void	ft_set_values(char **line, t_main *main)
{
	int		j;
	t_token	*token;

	token = ft_return_head(main->token);
	j = 0;
	while (token)
	{
		token->value = (char **)malloc(sizeof(char *) * \
							(ft_count_array(line[j], main) + 2));
		token->value[0] = ft_strdup(token->command);
		free(token->command);
		token->command = ft_find_path(token->value[0], main);
		ft_divide_line(line[j], token, main);
		if (token->next)
			token = token->next;
		else
			break ;
		j++;
	}
}
