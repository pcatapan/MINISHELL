# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 01:38:13 by aanghel           #+#    #+#              #
#    Updated: 2022/06/26 03:07:14 by pcatapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	./src/*.c \
		./src/utils/*.c

OBJC = $(SRC:%.c=%.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra #-fsanitize=thread

FLAG_READLINE = -lreadline -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib

all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) $(SRC) -o $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re: fclean all

.PHONY: all clean fclean re