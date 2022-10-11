# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aanghel <aanghel@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 19:54:47 by pcatapan          #+#    #+#              #
#    Updated: 2022/10/11 18:21:29 by aanghel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./src/*.c \
		./src/utils/*.c \
		./src/syntax/*.c \
		./src/parsing/*.c \
		./src/execute/*.c

OBJC = $(SRC:%.c=%.o)

CC = gcc

USER = pcatapan

#LDFLAGS = -L/opt/homebrew/opt/readline/lib
#CPPFLAGS = -I/opt/homebrew/opt/readline/include


FLAGS = #-Wall -Werror -Wextra #-g #-fsanitize=address

FLAG_READLINE = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -f 42minishell_history
	
re: fclean all

.PHONY: all clean fclean re