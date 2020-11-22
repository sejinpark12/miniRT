# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 18:23:05 by sejpark           #+#    #+#              #
#    Updated: 2020/11/22 18:31:11 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
OBJS = ${SRC:.c=.o}

NAME = mlx_exam
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGL -framework Appkit
RM = rm -f

all : ${NAME}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} -L ./ -lmlx ${FRAMEWORK} -o ${NAME} ${OBJS}

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean :
		${RM} ${OBJS} ${NAME}
