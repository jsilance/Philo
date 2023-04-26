# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 21:01:16 by jusilanc          #+#    #+#              #
#    Updated: 2023/04/26 14:29:42 by jusilanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c \

SRC = $(addprefix srcs/, $(SRCS))

CFLAGS = -Wall -Wextra -Werror -I includes/

OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
		@cc ${CFLAGS} ${OBJ} -o ${NAME}

all: ${NAME}

%.o: %.c
		@cc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		@rm -rf ${OBJ}

fclean: clean
		@rm -rf ${NAME}

re: fclean all
		@clear

.PHONY: all re clean fclean
