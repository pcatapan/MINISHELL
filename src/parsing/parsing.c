/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 18:58:00 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/02 22:57:58 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
}

void	ft_parsing(char *line, t_main *main)
{
	char	**tmp;
	char	*copy_line;
	int		i;
	int		count;
	char	*new_line;

	i = 0;
	count = 1;
	copy_line = ft_strdup(line);
	while (line[i])
	{
		i = ft_check_single_quote(line, main, i);
		i = ft_check_double_quote(line, main, i);
		i = ft_jump_brackets(line, i);
		if (line[i] == 38 || line[i] == 59 || line[i] == 124)
		{
			if (line[i + 1] == 38 || line[i + 1] == 124 || line[i] == 59 || \
							(line[i] == 124 && line[i - 1] != 124))
				count++;
			line[i] = 127;
			i++;
		}	
		else
			i++;
	}
	new_line = ft_add_space(line);
	main->copy_line = ft_strdup(new_line);
	tmp = ft_split_original(new_line, 127);
	ft_set_info(tmp, main, new_line, count);
	ft_free_matrix(tmp);
	free(copy_line);
	free(new_line);
}

int	ft_count_space(char *line)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		if ((line[i] == '<' && line[i + 1] != '<' && line[i - 1] != '<') \
				|| (line[i] == '>' && line[i + 1] != '>' && line[i - 1] != '>') \
				|| (line[i] == '<' && line[i + 1] == '<') \
				|| (line[i] == '>' && line[i + 1] == '>'))
			count++;
	}
	return (count);
}

char	*ft_add_space(char *tmp)
{
	char	*line;
	int		i;
	int		j;
	int		count;
	int		len;

	line = (char *)malloc(sizeof(char) * (ft_strlen(tmp) + \
				(ft_count_space(tmp) * 2) + 1));
	if (!line)
		return (0);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if ((tmp[i] == '<' && tmp[i + 1] == '<' && tmp[i - 1] != '<') \
				|| (tmp[i] == '>' && tmp[i + 1] == '>' && tmp[i - 1] != '>'))
		{
			line[j] = ' ';
			line[j + 1] = tmp[i];
			line[j + 2] = tmp[i + 1];
			line[j + 3] = ' ';
			j += 4;
			i += 2;
		}
		else if ((tmp[i] == '<' && tmp[i + 1] != '<' && tmp[i - 1] != '<') \
				|| (tmp[i] == '>' && tmp[i + 1] != '>' && tmp[i - 1] != '>'))
		{
			line[j] = ' ';
			line[j + 1] = tmp[i];
			line[j + 2] = ' ';
			j += 3;
			i++;
		}
		else
		{
			line[j] = tmp[i];
			j++;
			i++;
		}
	}
	line[j] = '\0';
	return (line);
}
