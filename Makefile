# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zanejar <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 22:41:40 by zanejar           #+#    #+#              #
#    Updated: 2022/11/16 22:41:43 by zanejar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

SOURCE = src/main.c src/lexer.c src/lexer2.c src/token.c src/lexer3.c \
		src/checker.c src/checker2.c src/parser.c src/parser2.c \
		src/utils.c src/utils2.c src/parser3.c

LIBFT = libft.a

RDLINE = -lreadline #-L/Users/zanejar/goinfre/.brew/opt/readline/lib -I /Users/zanejar/goinfre/.brew/opt/readline/include

OBJ = $(SOURCE:.c=.o)

RM = rm -Rf

all :		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(RDLINE) $(OBJ) -o $(NAME) $(LIBFT)

clean:
			$(RM) $(OBJ)

fclean: 	clean
			$(RM) $(NAME)

re: 		fclean all

.PHONY:		all clean fclean re