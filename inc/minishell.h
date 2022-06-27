/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:59:21 by pcatapan          #+#    #+#             */
/*   Updated: 2022/06/27 02:47:16 by pcatapan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <curses.h>
# include <signal.h>
# include <termios.h>
# include <stdbool.h>
# include <sys/stat.h>
# include <readline/history.h>
# include <readline/readline.h> 

# define NAME_SHELL "42minishell "
# define DIVISOR_SHELL " % "
# define HOME_SHELL " ~ "
# define FILE_HISTORY "/.42minishell_history"

typedef struct s_main
{
	int				input; //da valutare sia il tipo e sia se serve veramente
	int				output; //idem di input
	char			**copy_env;
	struct t_token	*token;
}	t_main;

typedef struct s_token
{
	char			command;
	char			value;
	char			sep;
	int				priority;
	struct t_token	*next;
	struct t_token	*prev;
}	t_token;

// Dir utils
size_t	ft_strlen(char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char    *ft_searchstrchr(char const *str, char **array);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strdup(const char *s1);
char	*ft_itoa(int n);
void	ft_putendl_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_strcmp(char *s1, char *s2);
int		ft_atoi(const char *str);

// free.c
void	ft_free_copy_env(char **copy_env);

// init_envp.c
void	ft_init_envp(char ***copy_envp, char **envp);

// prompt.c
void	ft_sig_handel(int signal);
int		ft_prompt(char **envp);

void    ft_add_history(char *line, char **envp);

#endif