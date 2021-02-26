# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 17:57:28 by sejpark           #+#    #+#              #
#    Updated: 2021/02/27 00:02:38 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main_test.c vec3.c ray.c hittable.c hittable_list.c sphere.c \
			  plane.c square.c cylinder1.c cylinder2.c triangle.c light.c \
			  ft_random.c ft_camera.c
OBJS 		= ${SRC:.c=.o}

NAME 		= miniRT
LIBFT 		= libft.a
LIBFTPATH 	= libft 
MLX 		= libmlx.dylib
MLXPATH 	= ./
CC 			= gcc
RM 			= rm -f
#CFLAGS 		= -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS 		= -Wall -Wextra -Werror
FRAMEWORK 	= -framework OpenGL -framework Appkit

all : 		${NAME}

${NAME} : 	${LIBFT} ${OBJS}
			@echo "\n\033[0;32mminiRT Building..."
			${CC} ${CFLAGS} -L${LIBFTPATH} -lft -L${MLXPATH} -lmlx \
											${FRAMEWORK} -o ${NAME} ${OBJS} 
			@echo "\033[0m"

${LIBFT} :
			@echo "\n\033[0;33mLibft Compiling..."
			cd ${LIBFTPATH}; make bonus 
			# ${MAKE} -C ${LIBFTPATH}
			cp ${LIBFTPATH}/${LIBFT} ./
			@echo "\033[0m"

.c.o :
			@echo "\n\033[0;32mminiRT Compiling..."
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}
			@echo "\033[0m"

clean :
			@echo "\033[0;31mCleaning..."
			${RM} ${OBJS}
			@echo "\033[0m"

fclean : 	clean
			@echo "\033[0;31mRemoving executable..."
			${RM} ${NAME} 
			@echo "\033[0m"

re : 		fclean all

.PHONY : 	all clean fclean re bonus
