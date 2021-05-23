# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/01 11:32:37 by sejpark           #+#    #+#              #
#    Updated: 2021/05/23 18:51:00 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#LIB_SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
#		ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
#		ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_isalpha.c \
#		ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_tolower.c \
#		ft_toupper.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
#		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c \
#		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
#
#BONUS_SRC = \
#		ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
#		ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
#		ft_lstmap.c
#
#LIB_OBJS = ${LIB_SRC:.c=.o}
#BONUS_OBJS = ${BONUS_SRC:.c=.o}

INC_DIR = includes

LIB_SRC_DIR = srcs/lib
BONUS_SRC_DIR = srcs/bonus

OBJ_DIR = objs
LIB_OBJ_DIR = objs/lib
BONUS_OBJ_DIR = objs/bonus

LIB_SRCS = ${wildcard ${LIB_SRC_DIR}/*.c}
BONUS_SRCS = ${wildcard ${BONUS_SRC_DIR}/*.c}

LIB_OBJS = ${LIB_SRCS:${LIB_SRC_DIR}/%.c=${LIB_OBJ_DIR}/%.o}
BONUS_OBJS = ${BONUS_SRCS:${BONUS_SRC_DIR}/%.c=${BONUS_OBJ_DIR}/%.o}

AR = ar
NAME = libft.a
CC = gcc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
INCPATH = ./

all : ${NAME}

lib_obj :
	mkdir -p ${LIB_OBJ_DIR}

bonus_obj :
	mkdir -p ${BONUS_OBJ_DIR}

$(NAME) : ${LIB_OBJS}
	${AR} rc ${NAME} ${LIB_OBJS}

bonus : ${LIB_OBJS} ${BONUS_OBJS}
	${AR} rc ${NAME} ${LIB_OBJS} ${BONUS_OBJS}

${LIB_OBJ_DIR}/%.o: ${LIB_SRC_DIR}/%.c 
	mkdir -p ${LIB_OBJ_DIR};
	${CC} ${CFLAGS} -c $< -o ${<:${LIB_SRC_DIR}/%.c=${LIB_OBJ_DIR}/%.o}

${BONUS_OBJ_DIR}/%.o: ${BONUS_SRC_DIR}/%.c
	mkdir -p ${BONUS_OBJ_DIR};
	${CC} ${CFLAGS} -c $< -o ${<:${BONUS_SRC_DIR}/%.c=${BONUS_OBJ_DIR}/%.o}

clean :
	${RM} ${LIB_OBJS} ${BONUS_OBJS} ${OBJ_DIR}

fclean : clean
	${RM} ${NAME}

re : fclean all


.PHONY : all clean fclean re bonus
