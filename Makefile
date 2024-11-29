NAME = minishell
CC = gcc
CFLAGS =  -I./include -I./libft #-Wall -Wextra -Werror
LIBFT = ./libft/libft.a

SRC_DIR = src
BUILD_DIR = build

SRC = $(shell find $(SRC_DIR) -name '*.c')
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -rf $(BUILD_DIR)
#make -C libft clean

fclean: clean
	rm -f $(NAME)
#make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
