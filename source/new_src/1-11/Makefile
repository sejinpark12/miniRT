# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sejpark <sejpark@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/10 17:57:28 by sejpark           #+#    #+#              #
#    Updated: 2021/03/10 14:23:49 by sejpark          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= main.c renderer.c vec1.c vec2.c vec3.c ray.c random.c camera.c \
			  hittable.c hittable_list1.c hittable_list2.c \
			  scene_reader.c parser_util1.c parser_util2.c parser_util3.c \
			  parser_list.c \
			  parser_ambient.c parser_resolution.c parser_camera.c \
			  parser_light.c parser_sphere.c parser_plane.c parser_square.c \
			  parser_cylinder.c parser_triangle.c get_next_line.c \
			  error_handler.c \
			  sphere.c plane.c square.c cylinder1.c cylinder2.c triangle.c \
			  light.c
#SRC			= main_test.c vec.c ray.c random.c camera.c \
#			  hittable.c hittable_list1.c hittable_list2.c \
#			  sphere.c plane.c square.c cylinder1.c cylinder2.c triangle.c \
#			  light.c
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
