/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 23:33:55 by pcatapan          #+#    #+#             */
/*   Updated: 2022/12/03 22:57:07 by fgrossi          ###   ########.fr       */
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
	main->first_part = ft_substr(str, 0, start - 1);
	main->second_part = ft_substr(str, start + l, ft_strlen(str));
	main->word = ft_substr(str, start, l);
	main->insert_word = ft_search_word(main->word, main->copy_env);
	if (main->insert_word == NULL)
	{
		main->insert_word = (char *)malloc(sizeof(char) * 1);
		if (!main->insert_word)
		{
			free(main->word);
			free(main->first_part);
			free(main->second_part);
			return (NULL);
		}
		main->insert_word[0] = '\0';
	}
	main->word = ft_strjoin(main->first_part, main->insert_word);
	free(main->insert_word);
	free(main->first_part);
	free(str);
	str = ft_strjoin(main->word, main->second_part);
	free(main->second_part);
	free(main->word);
	return (str);
}

char	*ft_expand_further(char *line, t_main *main, int i, int start)
{
	char	*tmp;
	int		l;

	l = 0;
	while (line[++i] && line[i] != ' ' && line[i] != '"' && line[i] != '\'' \
		&& line[i] != '$' && line[i] != 62 && line[i] != 60)
		l++;
	tmp = ft_strdup(line);
	free(line);
	if (tmp[start] == '?')
		line = ft_itoa(g_exit);
	else
		line = ft_change_var_in_dollar(start, l + 1, tmp, main);
	return (line);
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
	return (ft_expand_further(line, main, i, start));
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
