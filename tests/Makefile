NAME = tests.out

CC = gcc
LDLIBS = -lcriterion
RM = rm -rf
FORMAT = clang-format -i

SRC = keyboard.c
OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)%.o: %.c
	@${FORMAT} $<
	$(CC) -c $< -o $@

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDLIBS)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re