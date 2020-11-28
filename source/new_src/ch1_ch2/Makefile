# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/22 18:23:05 by sejpark           #+#    #+#              #
#    Updated: 2020/11/23 18:21:00 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c
SRC_KEY_DELAY = main_key_delay.c
OBJS = ${SRC:.c=.o}
OBJS_KEY_DELAY = ${SRC_KEY_DELAY:.c=.o}

NAME = fast
NAME_KEY_DELAY = delay
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FRAMEWORK = -framework OpenGL -framework Appkit
RM = rm -f

all : ${NAME} ${NAME_KEY_DELAY}

${NAME} : ${OBJS}
	${CC} ${CFLAGS} -L ./ -lmlx ${FRAMEWORK} -o ${NAME} ${OBJS}

${NAME_KEY_DELAY} : ${OBJS_KEY_DELAY}
	${CC} ${CFLAGS} -L ./ -lmlx ${FRAMEWORK} -o ${NAME_KEY_DELAY} ${OBJS_KEY_DELAY}

.c.o :
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean :
		${RM} ${OBJS} ${NAME} ${OBJS_KEY_DELAY} ${NAME_KEY_DELAY}
	
re : clean all
