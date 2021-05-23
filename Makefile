# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 17:57:28 by sejpark           #+#    #+#              #
#    Updated: 2021/05/23 20:16:56 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRC			= main.c renderer1.c renderer2.c renderer3.c bmp_creator.c \
#			  vec1.c vec2.c vec3.c ray.c random.c camera.c \
#			  hittable.c hittable_list1.c hittable_list2.c \
#			  scene_reader1.c scene_reader2.c parser_util1.c parser_util2.c \
#			  parser_util3.c parser_list.c error_handler.c \
#			  parser_ambient.c parser_resolution.c parser_camera.c \
#			  parser_light.c parser_sphere.c parser_plane.c parser_square.c \
#			  parser_cylinder.c parser_triangle.c get_next_line.c \
#			  sphere.c plane.c square.c cylinder1.c cylinder2.c triangle.c \
#			  light.c
#OBJS 		= ${SRC:.c=.o}

INC_DIR		= includes

SRC_DIR		= srcs
SRCS		= ${wildcard ${SRC_DIR}/*.c}

OBJ_DIR		= objs
OBJS		= ${SRCS:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

NAME 		= miniRT
LIBFT 		= libft.a
LIBFTPATH 	= ./library/libft
MLX 		= libmlx.dylib
MLXPATH 	= ./library/mlx
CC 			= gcc
RM 			= rm -rf
CFLAGS 		= -Wall -Wextra -Werror
FRAMEWORK 	= -framework OpenGL -framework Appkit

all : 		${NAME}

${NAME} : 	${LIBFT} ${OBJS}
			@echo "\n\033[0;32mminiRT Building..."
			cp ${MLXPATH}/${MLX} ./
			${CC} ${CFLAGS} -L./ -lft -L./ -lmlx ${FRAMEWORK} -o ${NAME} ${OBJS} 
			@echo "\033[0m"

${LIBFT} :
			@echo "\n\033[0;33mLibft Compiling..."
			cd ${LIBFTPATH}; make bonus 
			# ${MAKE} -C ${LIBFTPATH}
			cp ${LIBFTPATH}/${LIBFT} ./
			@echo "\033[0m"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
			@echo "\n\033[0;32mminiRT Compiling..."
			mkdir -p ${OBJ_DIR}
			${CC} ${CFLAGS} -c $< -o ${<:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}
			@echo "\033[0m"

clean :
			@echo "\033[0;31mCleaning..."
			cd ${LIBFTPATH}; make clean
			${RM} ${OBJS} ${OBJ_DIR}
			@echo "\033[0m"

fclean : 	clean
			@echo "\033[0;31mRemoving executable..."
			cd ${LIBFTPATH}; make fclean
			${RM} ${NAME} ${LIBFT} ${MLX}
			@echo "\033[0m"

re : 		fclean all

bonus :		${NAME}

.PHONY : 	all clean fclean re bonus
