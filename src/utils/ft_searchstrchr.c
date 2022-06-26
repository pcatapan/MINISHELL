/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_searchstrchr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 01:37:46 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/26 02:38:43 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char    *ft_searchstrchr(char *str, char **array)
{
    int i;
    int len;

    i = -1;
    len = ft_strlen(str);
    while (array[++i])
    {
        if(ft_strncmp(str, array[i], len) == 0)
            return (ft_substr(array[i], len, ft_strlen(array[i])));
    }
    return (NULL);    
}