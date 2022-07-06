/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrossi <fgrossi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:59:21 by pcatapan          #+#    #+#             */
/*   Updated: 2022/07/06 13:02:54 by fgrossi          ###   ########.fr       */
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
# include <sys/wait.h>
# include <readline/history.h>
# include <readline/readline.h> 

# define NAME_SHELL "42minishell "
# define DIVISOR_SHELL " % "
# define HOME_SHELL " ~ "
# define FILE_HISTORY "/.42minishell_history"
# define RED "\x1b[31m"
# define COLOR_RES  "\x1b[0m"
# define ERROR_DOUBLE_QUOTE "Mistake : unclosed double quotes"
# define ERROR_SING_QUOTE "Mistake : unclosed single quotes"
# define ERROR_BACKSLASH "Mistake : find the '\\'"

typedef struct s_token
{
	char			*token;
	char			**value;
	char			sep;
	int				priority;
	struct t_token	*next;
	struct t_token	*prev;
}	t_token;

typedef struct s_main
{
	int				quotes;
	char			**copy_env;
	char			*path;
	t_token			*token;
}	t_main;

// Dir utils
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_searchstrchr(char const *str, char **array);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char *charset);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strdup(const char *s1);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_itoa(int n);
void		ft_putendl_fd(char *s, int fd);
size_t		ft_strlen(char *s);

// free.c
void		ft_free_copy_env(char **copy_env);

// init_envp.c
char		**ft_init_envp(char **envp);

// prompt.c
int			ft_prompt(char **envp, t_main *main);
void		ft_sig_handel(int signal);

// history.c
void		ft_add_history(char *line, char **envp);

// syntax_check.c
void		ft_parsing(char *line);
void		ft_check_syntax(char *line, t_main *main);
int			ft_check_single_quote(char *line, t_main *main);
int			ft_check_double_quote(char *line, t_main *main);
void		ft_check_command(char *line, t_main *main);

// environment.c
int			ft_check_envi(char *line);
char		**ft_add_envi(char *line, t_main *main);

extern void	rl_replace_line(const char *text, int clear_undo);

// temporary
char	*find_path(char *cmd, t_main *main);
void 	check_built_in(char *cmd);
void 	ft_exit(void);
void	ft_cd(void);
void	ft_env(void);
void	ft_unset(void);
void	ft_echo(void);
void	ft_export(void);
void	ft_pwd(void);


#endif