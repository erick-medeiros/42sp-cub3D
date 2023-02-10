NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -I$(LIBFT_DIR)
CC = gcc
RM = rm -fr

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libs/libft/
MLX_DIR = libs/minilibx/

LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft -lm -lmlx -lXext -lX11

VALGRIND = valgrind -q --error-exitcode=1 --leak-check=full \
	--show-leak-kinds=all --track-origins=yes

# mandatory

NAME_MAN = mandatory/cub3D

FILES = main.c
FILES += canvas/canvas.c canvas/color.c canvas/draw.c canvas/pixel.c
FILES += core/game.c core/handle_events.c core/render.c core/render_map.c
FILES += debug/print_bits.c
FILES += utils/utils.c utils/debug.c
FILES += validation/validation.c
FILES += parser/parser.c

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
	$(VALGRIND) ./$(NAME) maps/exemple.cub

install:
	sudo apt install bear

install_mlx:
	cp scripts/install_mlx $(MLX_DIR)
	make -C $(MLX_DIR)
	cd $(MLX_DIR) && sudo bash ./install_mlx && rm install_mlx

bear:
	bear -- make re || bear make re

.PHONY: all clean fclean re bonus rebonus norm leaks install bear