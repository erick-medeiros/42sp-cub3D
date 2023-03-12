NAME = tests.out
CUB3D = ../cub3D
CUB3D_DIR = ../bonus/
LIBFT_DIR = ../libs/libft/

CC = gcc
CFLAGS = -I$(CUB3D_DIR)include/ -I$(LIBFT_DIR) -g -fsanitize=address
LDFLAGS = -L$(LIBFT_DIR)
LDLIBS = -lft -lm -lmlx -lXext -lX11 -lcriterion
RM = rm -rf
FORMAT = clang-format -i

SRC = keyboard.c validation_test.c parser_test.c render.c
SRC += minimap_bonus.c mouse_bonus.c collision_bonus.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.c
	@${FORMAT} $<
	@$(CC) $(CFLAGS) -c $< -o $@

$(CUB3D):
	@make -C ..

$(NAME): $(CUB3D) $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(wildcard $(CUB3D_DIR)obj/*/*.o) $(LDLIBS)

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
