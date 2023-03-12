NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -I$(LIBFT_DIR)
ifeq ($(DEBUG),1)
CFLAGS += -DDEBUG=1
endif
CC = gcc
RM = rm -fr

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libs/libft/
MLX_DIR = libs/minilibx/

LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft -lm -lmlx -lXext -lX11

VALGRIND = valgrind -q --error-exitcode=1 --leak-check=full \
	--suppressions=mlx_mouse_hide.supp --show-leak-kinds=all --track-origins=yes

# mandatory

NAME_MAN = mandatory/cub3D

FILES = main.c
FILES += canvas/canvas.c canvas/color.c canvas/draw.c canvas/pixel.c
FILES += canvas/bresenham.c canvas/layer.c
FILES += core/game.c core/init.c core/handle_events.c core/render.c
FILES += core/utils.c core/cleanup.c core/input_handler.c
FILES += debug/print_bits.c debug/vector.c debug/print_map.c debug/engine.c debug/framerate.c
FILES += utils/utils.c utils/vector1.c utils/vector2.c utils/vector3.c
FILES += utils/math.c
FILES += validation/validation.c validation/parameters.c validation/colors.c validation/utils.c validation/map.c
FILES += validation/map_attributes.c validation/map_sides.c validation/map_rows.c validation/map_borders.c
FILES += parser/parser.c parser/colors.c parser/textures.c parser/utils.c
FILES += raycaster/raycaster.c raycaster/texture.c raycaster/sprite.c
FILES += raycaster/dda_algorithm.c raycaster/collision.c

FILES += bonus/minimap.c bonus/minimap_fullscreen.c bonus/door.c bonus/door_file.c

INC_DIR = mandatory/include/
SRC_DIR = mandatory/src/
OBJ_DIR = mandatory/obj/
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
DIRS = $(sort $(dir $(OBJ)))

all: $(NAME_MAN)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME_MAN): $(DIRS) $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LDFLAGS) $(OBJ) -o $(NAME_MAN) $(LDLIBS)
	@cp $(NAME_MAN) $(NAME)

$(DIRS):
	@mkdir -p $@

# bonus

NAME_BONUS = bonus/cub3D_bonus

FILES_BONUS = main_bonus.c

INC_DIR_BONUS = bonus/include/
SRC_DIR_BONUS = bonus/src/
OBJ_DIR_BONUS = bonus/obj/
SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS), $(FILES_BONUS:.c=.o))
DIRS_BONUS = $(sort $(dir $(OBJ_BONUS)))

bonus: $(NAME_BONUS)

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR_BONUS) -c $< -o $@

$(NAME_BONUS): $(DIRS_BONUS) $(OBJ_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) -I$(INC_DIR_BONUS) $(OBJ_BONUS) -o $(NAME_BONUS)
	@cp $(NAME_BONUS) $(NAME)

$(DIRS_BONUS):
	@mkdir -p $@

# common

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_MAN) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

relibs:
	make re -C $(LIBFT_DIR)

norm:
	norminette mandatory/ bonus/ libs/libft/

leaks:
	$(VALGRIND) ./$(NAME) maps/square_10x10.cub

tests:
	make
	@make -C tests/
	@echo
	xvfb-run ./tests/tests.out

debug:
	make -e DEBUG=1

install:
#	sudo apt install bear xvfb
	sudo apt install libcriterion-dev clang-format

install_mlx:
	cp scripts/install_mlx $(MLX_DIR)
	make -C $(MLX_DIR)
	cd $(MLX_DIR) && sudo bash ./install_mlx && rm install_mlx

bear:
	bear -- make re || bear make re

.PHONY: all clean fclean re bonus rebonus norm leaks tests install bear