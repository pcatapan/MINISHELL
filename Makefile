# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 19:54:47 by pcatapan          #+#    #+#              #
#    Updated: 2022/10/15 19:00:23 by pcatapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./src/*.c \
		./src/utils/*.c \
		./src/syntax/*.c \
		./src/parsing/*.c \
		./src/execute/*.c \
		./src/bult_in/*.c

OBJC = $(SRC:%.c=%.o)

CC = gcc

USER = pcatapan

#LDFLAGS = -L/opt/homebrew/opt/readline/lib
#CPPFLAGS = -I/opt/homebrew/opt/readline/include


FLAGS = #-Wall -Werror -Wextra #-g #-fsanitize=address

# F_IRINA = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
FLAG_READLINE = -lreadline -lcurses -L/Users/$(USER)/.brew/opt/readline/lib -I/Users/$(USER)/.brew/opt/readline/include


all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(F_IRINA) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f 42minishell_history
	@rm -f file
	@rm -f heredoc
	
re: fclean all

.PHONY: all clean fclean re