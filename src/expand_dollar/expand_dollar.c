/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/04 05:56:26 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free_expand(char *str, char *str1, char *str2)
{
	if (str)
		free(str);
	if (str1)
		free(str1);
	if (str2)
		free(str2);
}

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
	char		*first_part;
	char		*second_part;
	char		*word;
	char		*insert_word;

	first_part = ft_substr(str, 0, start - 1);
	second_part = ft_substr(str, start + l, ft_strlen(str));
	word = ft_substr(str, start, l);
	insert_word = ft_search_word(word, main->copy_env);
	if (insert_word == NULL)
	{
		insert_word = (char *)malloc(sizeof(char) * 1);
		if (!insert_word)
		{
			ft_free_expand(word, first_part, second_part);
			return (NULL);
		}
		insert_word[0] = '\0';
	}
	word = ft_strjoin(first_part, insert_word);
	ft_free_expand(insert_word, first_part, str);
	str = ft_strjoin(word, second_part);
	ft_free_expand(NULL, second_part, word);
	return (str);
}

static void	ft_expand_support(char *line, int i)
{
	char	*tmp;

	line[i] = 127;
	while (line[i] != '}')
		i++;
	line[i] = 127;
	tmp = ft_strdup(line);
	free(line);
	line = ft_strtrim2(tmp, 127);
	free(tmp);
}

char	*ft_expand_doll(char *line, t_main *main, int i)
{
	char	*tmp;
	int		start;
	int		l;

	start = i;
	l = 0;
	if (line[i] == '{')
		ft_expand_support(line, i);
	while (line[++i] && line[i] != ' ' && line[i] != '"' && line[i] != '\'' \
	&& line[i] != '$' && line[i] != 62 && line[i] != 60)
		l++;
	tmp = ft_strdup(line);
	free(line);
	if (tmp[start] == '?')
	{
		line = ft_itoa(g_exit);
		free(tmp);
	}
	else
		line = ft_change_var_in_dollar(start, l + 1, tmp, main);
	return (line);
}
