# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pcatapan <pcatapan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/23 01:38:13 by aanghel           #+#    #+#              #
#    Updated: 2022/06/24 02:28:09 by pcatapan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/main \
		src/init_envp \
		./src/utils/ft_atoi.c \
		./src/utils/ft_strdup.c \
		./src/utils/ft_strjoin.c \
		./src/utils/ft_strlen.c \
		./src/utils/ft_strncmp.c \
		./src/free.c \

CC = gcc

FLAGS = -Wall -Werror -Wextra

FLAG_READLINE = -lreadline -I/opt/homebrew/opt/readline/include -L/opt/homebrew/opt/readline/lib

OBJC = $(SRC:.c=.o)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(FLAG_READLINE) -o $(NAME)
	
all: $(NAME)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)
	
re: all fclean 

.PHONY: all clean fclean re