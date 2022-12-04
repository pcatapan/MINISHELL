# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 19:54:47 by pcatapan          #+#    #+#              #
#    Updated: 2022/12/05 00:10:35 by pcatapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./PRINTF/*.c \
		./src/*.c \
		./src/utils/*.c \
		./src/syntax/*.c \
		./src/parsing/*.c \
		./src/execute/*.c \
		./src/execute/execve/*.c \
		./src/built_in/*.c \
		./src/redirection/*.c \
		./src/expand_dollar/*.c

OBJC = $(SRC:%.c=%.o)

CC = gcc

USER = pcatapan
HOME = /Users/${USER}

#LDFLAGS = -L/opt/homebrew/opt/readline/lib
#CPPFLAGS = -I/opt/homebrew/opt/readline/include

FLAGS = #-Wall -Werror -Wextra 

#F_IRINA = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
FLAG_READLINE =-lreadline -lcurses -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include


all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(F_IRINA) $(LDFLAGS) $(CPPFLAGS) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f ${HOME}/.42minishell_history
	@rm -f fil*
	@rm -f .heredoc
	@rm -f ${HOME}/.export
	@rm -f ${HOME}/.help
	@rm -rf *.dSYM
	
re: fclean all

.PHONY: all clean fclean re
