MCR		=	conditioner1.c \
			conditioner2.c

PRS		=	parse_all_params.c \
			parse_duplicate.c \
			parse_header.c \
			parse_map_checks.c \
			parse_map.c \
			parse_utils1.c \
			parse_utils2.c \
			parse_utils3.c

UTL		=	color_manager.c \
			get_next_line_utils.c \
			get_next_line.c \
			stack.c \
			utilities.c

PRSE	= $(addprefix Parser/, ${PRS})
MCRS	= $(addprefix Macros/, ${MCR})
UTLS	= $(addprefix Utilities/, ${UTL})	

SRC     =	${PRSE} \
			${MCRS} \
			${UTLS} \
			action_handler.c \
			bmp_save.c \
			display_frame.c \
			display_hud.c \
			display_last_frame.c \
			event_handler.c \
			intersection_manager.c \
			main.c \
			object_interaction.c \
			pre_setter.c \
			rotation_matrix.c \
			sprite_drawer.c \
			sprite_handler.c

SRCS    = $(addprefix srcs/, ${SRC})
OBJS    = ${SRCS:.c=.o}
INCS    = includes
MLX     = ./minilibx
NAME    = cub3D
LIBC    = ar rcs
CC      = gcc
RM      = rm -f
CFLAGS  = -Wall -Wextra -Werror -O2
srcs/%.o: srcs/%.c ${INCS}
	${CC} ${CFLAGS} -c $< -o $@ -I ${INCS}
${NAME}: ${OBJS}
	@${MAKE} bonus -C ./libft
	@${MAKE} -C ${MLX}
	${CC} -L${MLX} -lmlx -framework OpenGL -framework AppKit -o ${NAME} ${OBJS} libft/libft.a ${MLX}/libmlx.a
all: ${NAME}
bonus: all
clean:
	${MAKE} clean -C ./libft
	${MAKE} clean -C ${MLX}
	${RM} ${OBJS}
	${RM} a.out
fclean: clean
	${MAKE} fclean -C ./libft
	${MAKE} clean -C ${MLX}
	${RM} ${NAME}
re: fclean all
.PHONY: all clean fclean re .c.o