# Variables

NAME_CLI = client
NAME_SER = server

CC = gcc

SRC_FILES_CLI = client
SRC_FILES_SER = server

SRC_DIR = ./src/
OBJ_DIR = ./obj/

CFLAGS = -Wall -Wextra -Werror -Ilibft/include -Iinclude

SRC_CLI = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_CLI)))
SRC_SER = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES_SER)))

OBJ_CLI = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_CLI)))
OBJ_SER = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES_SER)))

LIB = $(addprefix $(LIB_PATH), libft.a)

LIB_PATH = libft/

LIB_INCLUDE = libft/include

MAKE := make

GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
NC=\033[0m

# Phony targets
.PHONY: all clean fclean re libft bonus

# Rules
all: $(NAME_CLI) $(NAME_SER)

$(LIB):
	@cd ./libft && $(MAKE) > /dev/null && $(MAKE) bonus > /dev/null && $(MAKE) printf > /dev/null
	@echo "$(GREEN)Built Libft ✅ $(NC)"

$(NAME_CLI): $(OBJ_CLI) $(LIB)
	@$(CC) -Llibft -o $@ $^ -lft $(CFLAGS)
	@echo "$(BLUE)Compiled $(NAME_CLI) ✅ $(NC)"

$(NAME_SER): $(OBJ_SER) $(LIB)
	@$(CC) -Llibft -o $@ $^ -lft $(CFLAGS)
	@echo "$(BLUE)Compiled $(NAME_SER) ✅ $(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(MAGENTA)Cleaned object files ✅ $(NC)"

fclean: clean
	@cd ./libft && $(MAKE) fclean > /dev/null
	@echo "$(MAGENTA)Cleaned libft ❎ $(NC)"
	@$(RM) -f $(NAME_CLI)
	@$(RM) -f $(NAME_SER)
	@echo "$(MAGENTA)Cleaned $(NAME_CLI) and $(NAME_SER) ❎ $(NC)"

re: fclean all