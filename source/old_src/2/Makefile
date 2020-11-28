# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 17:57:28 by sejpark           #+#    #+#              #
#    Updated: 2020/11/27 19:50:56 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c vec3.c ray.c
OBJS 		= ${SRC:.c=.o}

AR 			= ar
NAME 		= miniRT
LIBFT 		= libft.a
LIBFTPATH 	= ./ 
MLX 		= libmlx.dylib
MLXPATH 	= ./
CC 			= gcc
RM 			= rm -f
CFLAGS 		= -Wall -Wextra -Werror
FRAMEWORK 	= -framework OpenGL -framework Appkit

all : 		${NAME}

${NAME} : 	${LIBFT} ${MLX} ${OBJS}
			@echo "\n\033[0;32mminiRT Building..."
			${CC} ${CFLAGS} -L${LIBFTPATH} -lft -L${MLXPATH} -lmlx ${FRAMEWORK} -o ${NAME} ${OBJS} 
			@echo "\033[0m"

${LIBFT} :
			@echo "\n\033[0;33mLibft Compiling..."
			${MAKE} -C ${LIBFTPATH}
			cp ${LIBFTPATH}/${LIBFT} ./
			@echo "\033[0m"

${MLX} :
			@echo "\n\033[0;33mmlx Compiling..."
			${MAKE} -C ${MLXPATH}
			cp ${MLXPATH}/${MLX} ./
			@echo "\033[0m"

.c.o :
			@echo "\n\033[0;32mminiRT Compiling..."
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
			@echo "\033[0m"

clean :
			@echo "\033[0;31mCleaning..."
			cd ${LIBFTPATH}; make clean
			cd ${MLXPATH}; make clean
			${RM} ${OBJS}
			@echo "\033[0m"

fclean : 	clean
			@echo "\033[0;31mRemoving executable..."
			cd ${LIBFTPATH}; make fclean
			${RM} ${NAME} ${LIBFT} ${MLX}
			@echo "\033[0m"

re : 		fclean all

.PHONY : 	all clean fclean re bonus
