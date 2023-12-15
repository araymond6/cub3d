NAME = cub3D
LIBFT = $(LIB_DIR)libft.a
MLX42 = MLX42/build/libmlx42.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g #-fsanitize=address
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -I /include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

SRC_DIR = src/
INC_DIR = include/
LIB_DIR = libft/
MLX_DIR = MLX42/
BUILD_DIR = $(MLX_DIR)build
OBJ_DIR = obj/

SRCS =	main.c \
		parsing.c \
		get_rgb_value.c \
		get_player_pos.c \
		get_map.c \
		get_player_pos.c \
		raycast.c \
		raycast2.c \
		movement.c \
		texture.c \
		utils_parsing.c \
		utils_parsing2.c \
		utils.c \
		utils2.c
VPATH = $(SRC_DIR) $(INC_DIR)

OBJS = $(SRCS:%.c=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

INC = cub3D.h
INC_PRE = $(addprefix $(INC_DIR), $(INC))

BREW = /Users/$(USER)/.brew/bin/brew
DEP_INSTALLED := .dep_installed
MLX_INSTALLED := .mlx_installed

#COLORS
YELLOW = \033[93m
BLUE = \033[94m
RESET = \033[0m

all: dep lib mlx $(NAME)

$(OBJ_DIR)%.o: %.c $(INC_PRE)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<
	@echo "$(YELLOW)$< compiled!$(RESET)"

$(NAME): $(OBJ_PRE)
	@echo "$(YELLOW)Compiling files...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(MLX42) $(MLX_FLAGS)
	@echo "$(YELLOW)Files compiled!$(RESET)"

re: fclean all

mlx: | $(MLX_INSTALLED)

$(MLX_INSTALLED):
	@echo "$(YELLOW)Checking MLX42...$(RESET)"
	@if [ ! -f $(MLX42) ]; then \
		(cd $(MLX_DIR) && cmake -B build/); \
		(make -C $(BUILD_DIR)); \
		fi
	@touch $(MLX_INSTALLED)
	@echo "$(YELLOW)MLX42 built!$(RESET)"

dep: | $(DEP_INSTALLED)

$(DEP_INSTALLED):
	@echo "$(YELLOW)Checking dependencies...$(RESET)"
	@if [ ! -f $(BREW) ]; then \
		yes | -/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"; \
		fi
	@if ! brew list | grep -q "cmake"; then \
		brew install cmake; \
		fi
	@if ! brew list | grep -q "glfw"; then \
		brew install glfw; \
		fi
	@touch $(DEP_INSTALLED)
	@echo "$(YELLOW)Dependencies installed!$(RESET)"

lib: $(LIBFT)

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@make -C $(LIB_DIR)
	@echo "$(YELLOW)Libft built!$(RESET)"

clean:
	@echo "$(YELLOW)Removing object files...$(RESET)"
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)
	@if [ -f $(BUILD_DIR) ]; then \
		make clean -C $(BUILD_DIR); \
		fi
	@echo "$(YELLOW)Files removed!$(RESET)"

fclean: clean
	@echo "$(YELLOW)Removing program and dependency files...$(RESET)"
	rm -rf $(NAME)
	rm -rf $(BUILD_DIR)
	rm -rf $(DEP_INSTALLED)
	rm -rf $(MLX_INSTALLED)
	make fclean -C $(LIB_DIR)
	@echo "$(YELLOW)Files removed!$(RESET)"

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --suppressions=supp.txt ./$(NAME) maps/pig.cub

.PHONY: re fclean clean all run mlx dep val lib