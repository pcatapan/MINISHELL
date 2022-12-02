/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/02 20:42:35 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_search_word(char *word, char **env)
{
	char	*tmp;
	char	*rtr;

	tmp = ft_strjoin(word, "=");
	free(word);
	rtr = ft_searchstrchr(tmp, env);
	free (tmp);
	return (rtr);
}

char	*ft_change_var_in_dollar(int start, int l, char *str, t_main *main)
{
	char	*first_part;
	char	*second_part;
	char	*word;
	char	*insert_word;

	first_part = ft_substr(str, 0, start - 1);
	second_part = ft_substr(str, start + l, ft_strlen(str));
	word = ft_substr(str, start, l);
	insert_word = ft_search_word(word, main->copy_env);
	if (insert_word == NULL)
	{
		insert_word = (char *)malloc(sizeof(char) * 1);
		if (!insert_word)
		{
			free(word);
			free(first_part);
			free(second_part);
			return (NULL);
		}
		insert_word[0] = '\0';
	}
	word = ft_strjoin(first_part, insert_word);
	free(insert_word);
	free(first_part);
	free(str);
	str = ft_strjoin(word, second_part);
	free(second_part);
	free(word);
	return (str);
}

char	*ft_expand_doll(char *line, t_main *main, int i)
{
	char	*tmp;
	int		start;
	int		l;

	start = i;
	l = 0;
	if (line[i] == '{')
	{
		line[i] = 127;
		while (line[i] != '}')
			i++;
		line[i] = 127;
		tmp = ft_strdup(line);
		free(line);
		line = ft_strtrim2(tmp, 127);
		free(tmp);
	}
	while (line[++i] && line[i] != ' ' && line[i] != '"' && line[i] != '\'' \
		&& line[i] != '$' && line[i] != 62 && line[i] != 60)
		l++;
	tmp = ft_strdup(line);
	free(line);
	line = ft_change_var_in_dollar(start, l + 1, tmp, main);
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

int	ft_check_expand(char *line, int i)
{
	bool	dollar;
	int		count;

	dollar = FALSE;
	count = 1;
	if (line[i] == '$')
		dollar = TRUE;
	else
		return (0);
	if ((line[i + 1] == '$' || line[i - 1] == '$') && dollar)
		return (0);
	while (i > 0)
	{
		if (line[i] == '"')
			count++;
		i--;
	}
	if ((count % 2) == 0 && !ft_strchr(line, '"'))
		return (0);
	if (dollar)
		return (1);
	return (0);
}
