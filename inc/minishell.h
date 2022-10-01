/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:59:21 by pcatapan          #+#    #+#             */
/*   Updated: 2022/09/30 12:58:54 by pcatapan         ###   ########.fr       */
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
# define ERROR_OPEN_BRACKETS "Mistake : find open brackets exstra"
# define ERROR_CLOSE_BRACKETS "Mistake : find close brackets exstra"
# define ERROR_OP_LOGIC "Syntax error near unexpected token"

typedef struct s_token
{
	char			*command;
	char			**value;
	int				priority;
	// bool per here_doc
	// char *parola di stop
	// bool pipe
	// char *res_str
	bool			or;
	bool			and;
	bool			res;
	struct s_main	*main;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_main
{
	t_token		*token;
	char		**copy_env;
	bool		op_logic;
	bool		error;
	int			open_brackets;
	int			close_brackets;
	int			dub_quotes;
	int			sin_quotes;
}	t_main;

// DIR Utils
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strchr(const char *s, int c);
int			ft_strcmp(char *s1, char *s2);
int			ft_lstsize(t_token *lst_or);
int			ft_atoi(const char *str);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_searchstrchr(char const *str, char **array);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char *charset);
char		**ft_split_original(char const *s, char c);
char		*ft_strcat(char *dest, const char *src);
char		*ft_strdup(const char *s1);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_token **lst, t_token *new);
void		ft_lstcopy(t_token **lst, t_token *new);
void		ft_putendl_fd(char *s, int fd);
t_token		*ft_lstnew(void *content);
size_t		ft_strlen(char *s);

// free.c
void		ft_free_matrix(char **matrix);

// init_envp.c
char		**ft_init_envp(char **envp);

// prompt.c
int			ft_prompt(char **envp, t_main *main);
void		ft_sig_handel(int signal);

// history.c
void		ft_add_history(char *line, char **envp);

// DIR syntax_check
void		ft_check_syntax(char *line, t_main *main);
int			ft_check_single_quote(char *line, t_main *main, int i);
int			ft_check_double_quote(char *line, t_main *main, int i);
void		ft_check_command(char *line, t_main *main);

// environment.c
int			ft_check_envi(char *line);
char		**ft_add_envi(char *line, t_main *main);

// DIR Parsing
char		*find_path(char *cmd, t_main *main);
char		*ft_find_token(char *line, t_main *main);
void		ft_parsing(char *line, t_main *main);
void		ft_set_op_logic(char *line, t_token *token);
void		ft_set_values(char **line, t_main *main);
void		ft_set_priority(char *line, t_main *main, int brack);
t_token		*ft_return_head(t_token *list);

extern void	rl_replace_line(const char *text, int clear_undo);

// temporary
void		check_built_in(t_main *main);
void		ft_exit(void);
void		ft_cd(void);
void		ft_env(void);
void		ft_unset(void);
void		ft_echo(void);
void		ft_export(void);
void		ft_pwd(void);
void		ft_print_lst(t_token *a);

#endif