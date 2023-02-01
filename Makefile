NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
CC = cc
RM = rm -fr

LIBFT = $(LIBFT_DIR)libft.a
LIBFT_DIR = libs/libft/
MINILIBX = $(MINILIBX_DIR)libmlx.a
MINILIBX_DIR = libs/minilibx/

LDFLAGS = -L$(LIBFT_DIR) -L$(MINILIBX_DIR)
LDLIBS = -lft -lm -lmlx -lXext -lX11

VALGRIND = valgrind -q --leak-check=full --show-leak-kinds=all \
	--track-fds=yes --track-origins=yes

# mandatory

NAME_MAN = mandatory/cub3D

FILES = main.c handle_events.c
FILES += canvas/canvas.c canvas/color.c canvas/draw.c canvas/pixel.c
FILES += debug/print_bits.c

INC_DIR = mandatory/include/
SRC_DIR = mandatory/src/
OBJ_DIR = mandatory/obj/
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
DIRS = $(sort $(dir $(OBJ)))

all: $(NAME_MAN)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) $(LDFLAGS) -c $< -o $@ $(LDLIBS)

$(NAME_MAN): $(DIRS) $(OBJ) $(LIBFT) $(MINILIBX)
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

$(NAME_BONUS): $(DIRS_BONUS) $(OBJ_BONUS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) -I$(INC_DIR_BONUS) $(OBJ_BONUS) -o $(NAME_BONUS)
	@cp $(NAME_BONUS) $(NAME)

$(DIRS_BONUS):
	@mkdir -p $@

# common

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(RM) $(NAME) $(NAME_MAN) $(NAME_BONUS)

re: fclean all

rebonus: fclean bonus

relibs:
	make re -C $(LIBFT_DIR)
	make re -C $(MINILIBX_DIR)

norm:
	norminette mandatory/ bonus/ libs/libft/ | grep Error | cat

leaks:
	$(VALGRIND) ./$(NAME)

install:
	sudo apt install bear

bear:
	bear -- make re || bear make re

.PHONY: all clean fclean re bonus rebonus norm leaks install bear