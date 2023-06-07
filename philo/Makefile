# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 21:01:16 by jusilanc          #+#    #+#              #
#    Updated: 2023/06/08 01:35:00 by jusilanc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c ft_philo_init.c ft_atoi.c ft_isdigit.c ft_philosophe.c ft_philosophe_utils.c \
		ft_philo_eat.c ft_philo_sleep.c ft_philo_think.c philo_death_part.c \

SRC = $(addprefix srcs/, $(SRCS))

CFLAGS = -Wall -Wextra -Werror -I includes/

LDFLAGS = -pthread

OBJ = ${SRC:.c=.o}

${NAME}: ${OBJ}
		gcc ${CFLAGS} ${OBJ} ${LDFLAGS} -o ${NAME}

all: ${NAME}

%.o: %.c
		cc ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
		rm -rf ${OBJ}

fclean: clean
		rm -rf ${NAME}

re: fclean all

.PHONY: all re clean fclean
