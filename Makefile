CFLAGS = -Wall -Wextra -Werror -g
CFLAGS += -I$(LIBFT_DIR) -I$(MINILIBX_DIR) -Iinclude/
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

BIN_DIR = bin/

# mandatory

NAME = cub3D

FILES = main.c mlx_extra.c handle_events.c

SRC_DIR = src/
OBJ_DIR = obj/
SRC = $(addprefix $(SRC_DIR), $(FILES))
OBJ = $(addprefix $(OBJ_DIR), $(FILES:.c=.o))
DIRS = $(sort $(dir $(OBJ)))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@ $(LDLIBS)

$(NAME): $(DIRS) $(BIN_DIR) $(OBJ) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJ) -o $(BIN_DIR)$(NAME) $(LDLIBS)
	@cp $(BIN_DIR)$(NAME) $(NAME)

$(DIRS):
	@mkdir -p $@

# bonus

NAME_BONUS = cub3D_bonus

FILES_BONUS = main_bonus.c

SRC_DIR_BONUS = bonus/
OBJ_DIR_BONUS = obj_bonus/
SRC_BONUS = $(addprefix $(SRC_DIR_BONUS), $(FILES_BONUS))
OBJ_BONUS = $(addprefix $(OBJ_DIR_BONUS), $(FILES_BONUS:.c=.o))
DIRS_BONUS = $(sort $(dir $(OBJ_BONUS)))

bonus: $(NAME_BONUS)

$(OBJ_DIR_BONUS)%.o: $(SRC_DIR_BONUS)%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_BONUS): $(DIRS_BONUS) $(BIN_DIR) $(OBJ_BONUS) $(LIBFT) $(MINILIBX)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(BIN_DIR)$(NAME_BONUS)
	@cp $(BIN_DIR)$(NAME_BONUS) $(NAME)

$(DIRS_BONUS):
	@mkdir -p $@

# common

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MINILIBX):
	make -C $(MINILIBX_DIR)

$(BIN_DIR):
	@mkdir -p $@

clean:
	$(RM) $(OBJ_DIR) $(OBJ_DIR_BONUS)

fclean: clean
	$(RM) $(BIN_DIR) $(NAME)

re: fclean all

rebonus: fclean bonus

relibs:
	make re -C $(LIBFT_DIR)
	make re -C $(MINILIBX_DIR)

norm:
	norminette src/ include/ bonus/ libs/libft/ | grep Error | cat

leaks:
	$(VALGRIND) ./$(NAME)

install:
	sudo apt install bear

bear:
	bear -- make re || bear make re

.PHONY: all clean fclean re bonus rebonus norm leaks install bear