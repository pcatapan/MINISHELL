/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 19:04:57 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/07 17:41:57 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/minishell.h"

static int	ft_is_charset(char str, char *charset)
{
	while (*charset)
	{
		if (str == *charset)
			return (1);
		charset++;
	}
	return (0);
}

static int	ft_wordlen(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_charset(str[i], charset) == 0)
		i++;
	return (i);
}

static int	ft_wordcount(char *str, char *charset)
{
	int	i;
	int	j;

	j = 0;
	while (*str)
	{
		while (*str && ft_is_charset(*str, charset) == 1)
			str++;
		i = ft_wordlen(str, charset);
		str += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*ft_strdupp(char *src, int j)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc((j + 1) * sizeof(char));
	if (!dst)
		return (0);
	while (i < j && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**ft_split_2(char const *s, char *charset)
{
	char		**dest;
	int			size;
	int			i;
	int			j;

	i = -1;
	if (!s || !charset)
		return (0);
	size = ft_wordcount((char *)s, charset);
	dest = malloc((size + 1) * sizeof(char *));
	if (!dest || !s)
		return (0);
	while (++i < size)
	{
		while (ft_is_charset((char)*s, charset))
			s++;
		j = ft_wordlen((char *)s, charset);
		dest[i] = ft_strdupp((char *)s, j);
		s += j;
	}
	dest[size] = 0;
	return (dest);
}

int	main(void)
{
	char	*one;
	char	**result;
	char	*segni;
	int i;

	segni = malloc(sizeof(char) * 6);
	segni[0] = 32;
	segni[1] = 92;
	segni[2] = 34;
	segni[3] = 39;
	segni[4] = 59;
	segni[5] = '\0';
	one = malloc(sizeof(char *) * 20);
	one = "ciao\"come;stai\'scemo nero\\";
	result = ft_split_2(one, segni);
	while (result[i])
	{
		printf("%s\n", result[i]);
		i++;
	}
	free(segni);
	ft_free_copy_env(result);
	// one[0] = "pwd";
	// one[1] = "Messaggio";
	// if (execve("pwd", one, envp))
	// 	perror("TEST");
}

void	ft_print_lst(t_token *a)
{
	while (a)
	{
		printf("%s\n", a->command);
		a = a->next;
	}	
}