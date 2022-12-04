/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:58:00 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 04:40:17 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_count_space(char *line)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			if (line[i - 1] != '<' && line[i - 1] != '>')
				count++;
			else if (line[i + 1] != '<' && line[i + 1] != '>')
				count++;
		}
	}
	return (count);
}

static int	ft_add_space(char *tmp, int i, char *line, int j)
{
	if (tmp[i - 1] != '<' && tmp[i - 1] != '>')
		line[j++] = ' ';
	line[j] = tmp[i];
	if (tmp[i + 1] != '<' && tmp[i + 1] != '>')
		line[++j] = ' ';
	return (j);
}

static char	*ft_preparate_space(char *tmp)
{
	char	*line;
	int		i;
	int		j;

	i = -1;
	j = 0;
	line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + \
				(ft_count_space(tmp) * 2) + 1));
	if (!line)
		return (0);
	while (tmp[++i])
	{
		if (tmp[i] == '>' || tmp[i] == '<')
			j = ft_add_space(tmp, i, line, j);
		else
			line[j] = tmp[i];
		j++;
	}
	line[j] = '\0';
	free(tmp);
	return (line);
}

void	ft_set_info(char **tmp, t_main *main, char *copy_line, int count)
{
	char	**tmp_value;
	int		i;
	bool	first;

	first = TRUE;
	tmp_value = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tmp_value)
		return ;
	i = -1;
	while (tmp[++i])
	{
		tmp_value[i] = ft_find_token(tmp[i], main, first);
		first = FALSE;
	}
	tmp_value[i] = NULL;
	ft_set_values(tmp_value, main);
	ft_set_op_logic(copy_line, main->token);
	ft_set_priority(copy_line, main, 0);
	ft_set_redirections(main->token);
	ft_free_matrix(tmp_value);
	ft_free_matrix(tmp);
	free(copy_line);
}

void	ft_parsing(char *line, t_main *main)
{
	char	**tmp;
	char	*copy_line;
	int		i;
	int		count;

	i = 0;
	count = 1;
	line = ft_preparate_space(line);
	main->copy_line = ft_strdup(line);
	copy_line = ft_strdup(line);
	while (line[i])
	{
		i = ft_support_parsing(line, main, i);
		if (line[i] == 38 || line[i] == 59 || line[i] == 124)
		{
			if (line[i + 1] == 38 || line[i + 1] == 124 || line[i] == 59 || \
							(line[i] == 124 && line[i - 1] != 124))
				count++;
			line[i] = 127;
		}
		i++;
	}
	tmp = ft_split_original(line, 127);
	ft_set_info(tmp, main, copy_line, count);
	free(line);
}
