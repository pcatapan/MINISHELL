/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/11/20 05:25:23 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_change_var_in_dollar(int start, int l, char *str, t_main *main)
{
	char	*first_part;
	char	*second_part;
	char	*word;
	char	*insert_word;

	first_part = ft_substr(str, 0, start - 1);
	second_part = ft_substr(str, start + l, ft_strlen(str));
	word = ft_substr(str, start, l);
	insert_word = ft_searchstrchr(ft_strjoin(word, "="), main->copy_env);
	if (insert_word == NULL)
	{
		insert_word = (char *)malloc(sizeof(char) * 1);
		insert_word[0] = '\0';
	}
	free(word);
	word = ft_strjoin(first_part, insert_word);
	free(insert_word);
	free(first_part);
	free(str);
	str = ft_strjoin(word, second_part);
	free(second_part);
	free(word);
	return (str);
}

char	*ft_expand_dollar(char *line, t_main *main)
{
	int		i;
	int		l;
	int		start;

	i = 0;
	l = 0;
	start = 0;
	if (ft_strchr(line, 123) && ft_strchr(line, 125))
		line = ft_strtrim3(line, "{ }");
	// line = ft_delete_brackets(line);
	while (line[i] != '$' && line[i])
	{
		i = ft_check_single_quote(line, main, i);
		i++;
	}
	if (line[i] == '$')
		start = i + 1;
	while (line[i++] && line[i] != ' ' && line[i] != '"' && line[i] != '\'' \
		&& line[i] != '$' && line[i] != 62 && line[i] != 60)
		l++;
	if (start != 0 && start != 1)
		line = ft_change_var_in_dollar(start, l, line, main);
	return (line);
}

char	*ft_expand_heredoc(char *line, t_main *main)
{
	int	i;
	int	l;
	int	start;

	i = 0;
	l = 0;
	start = 0;
	while (line[i] != '$' )
		i++;
	if (line[i] == '$')
		start = i + 1;
	while (line[++i] && line[i] != ' ' && line[i] != '"')
		l++;
	if (start != 0)
		line = ft_change_var_in_dollar(start, l, line, main);
	return (line);
}

char	*ft_delete_brackets(char *line)
{
	char	*tmp;
	char	*rtr;

	tmp = ft_strdup(line);
	free(line);
	tmp = ft_clear_brackets(tmp);
	rtr = ft_strdup("$\0");
	rtr = ft_strcat(rtr, tmp);
	free(tmp);
	return (rtr);
}
