# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anclarma <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/08 23:58:07 by anclarma          #+#    #+#              #
#    Updated: 2021/01/27 15:25:37 by anclarma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT
FLAGS		= -Wall -Wextra -Werror \
			  -O3
MLX_LINUX	= -L ./minilibx-linux \
			  -I ./minilibx-linux \
			  -lm -lmlx -lXext -lX11 -lpthread
MLX_MAC		= -L ./minilibx-mac \
			  -I ./minilibx-mac \
			  -lmlx -framework OpenGL -framework AppKit
INCLUDES	= -I ./libft \
			  -I ./includes
LIB_LIBFT	= -L ./libft \
			  -lft
C_FILES		= main.c \
			  lst_obj.c \
			  parsing.c \
			  res.c \
			  exit_err.c \
			  to_char.c \
			  read_line.c \
			  check_file.c \
			  amb_light.c \
			  lst_cam.c \
			  lst_light.c \
			  lst_sphere.c \
			  lst_plane.c \
			  lst_square.c \
			  lst_cylinder.c \
			  lst_triangle.c \
			  lst_cone.c \
			  rot_vector.c \
			  lst_cube.c \
			  vector1.c \
			  vector2.c \
			  vector3.c \
			  extremum.c \
			  lst_pyramid.c \
			  input.c \
			  render.c \
			  scenescan.c \
			  getcolor.c \
			  check.c \
			  this_obj_is.c \
			  albedo.c \
			  intersect.c \
			  inter_sphere.c \
			  inter_plane.c \
			  inter_square.c \
			  inter_cylinder.c \
			  inter_triangle.c \
			  inter_cone.c \
			  screenshot.c \
			  to_bmp.c \
			  add_amb_light.c \
			  tmp_lst_obj.c
SRCS		= $(addprefix srcs/,$(C_FILES))
OBJS		= $(SRCS:.c=.o)
UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
    MLX = $(MLX_MAC)
    MACRO = -D MACOS
    PATH_MLX = minilibx-mac
endif
ifeq ($(UNAME),Linux)
    MLX = $(MLX_LINUX)
    MACRO = -D LINUX
    PATH_MLX = minilibx-linux
endif

.c.o:
	@clang $(FLAGS) $(INCLUDES) $(MACRO) -c $< -o $(<:.c=.o)
	@printf "\033[32;1mcompil %s: %20.20s\033[0m\r" $(NAME) $<

all:		$(NAME)

$(NAME):	sub-make $(OBJS)
	@clang $(FLAGS) $(INCLUDES) $(SRCS) $(LIB_LIBFT) $(MLX) $(MACRO) -o $(NAME)
	@printf "\033[32;1m%s OK%30.30s\n\033[0m" $(NAME) ""

sub-make:
	@make -C libft all
	@printf "\033[32;1m%s OK%30.30s\n\033[0m" "libft" ""
	@make -C $(PATH_MLX) all
	@printf "\033[32;1m%s OK%30.30s\n\033[0m" $(PATH_MLX) ""

clean:
	@make -C libft clean
	@make -C $(PATH_MLX) clean
	@rm -f $(OBJS)
	@printf "\033[32;1m%s OK%30.30s\n\033[0m" "clean" ""

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)

re:			fclean all

debug:		sub-make
	clang -Wall -Wextra -Werror -lm -Ofast  -I /usr/local/include -I ./libft -I ./tmp_includes $(TMP_SRCS) -L /usr/local/lib $(MLX) -o test_parseur.out

mac:		sub-make
	@clang $(FLAGS) $(INCLUDES) $(SRCS) $(LIB_LIBFT) $(MLX) -o test_parseur.out
	@printf "\033[32;1m%s en mode test pour mac OK%30.30s\n\033[0m\r" $(NAME) ""
.PHONY:	all	$(NAME) clean fclean re install debug
