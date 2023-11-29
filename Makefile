NAME = cub3D
LIBFT = $(LIB_DIR)libft.a
MLX42 = MLX42/build/libmlx42.a

CC = gcc
CFLAGS = -g
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -I /include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"

SRC_DIR = src/
INC_DIR = include/
LIB_DIR = libft/
MLX_DIR = MLX42/
BUILD_DIR = $(MLX_DIR)build
OBJ_DIR = obj/

SRCS =	main.c \
		raycast.c \
		raycast2.c \
		utils.c
VPATH = $(SRC_DIR) $(INC_DIR)

OBJS = $(SRCS:%.c=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

INC = cub3D.h
INC_PRE = $(addprefix $(INC_DIR), $(INC))

BREW = /Users/$(USER)/.brew/bin/brew
CMAKE = /Users/$(USER)/.brew/bin/cmake
GLFW = /Users/$(USER)/.brew/Cellar/glfw

OS = $(shell uname)
ifeq ($(OS), Linux)
	MLX_FLAGS = -Iinclude -ldl -lglfw -pthread -lm
	NOTMAC = 1
else ifeq ($(OS), Darwin)
	MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit -I /include -lglfw -L "/Users/$(USER)/.brew/opt/glfw/lib/"
	NOTMAC = 0
endif

#COLORS
YELLOW = \033[93m
BLUE = \033[94m
RESET = \033[0m

all: lib mlx $(NAME)

$(OBJ_DIR)%.o: %.c $(INC_PRE)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJ_PRE)
	@echo "$(YELLOW)Compiling files...$(RESET)"
	$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(MLX42) $(MLX_FLAGS)
	@echo "$(YELLOW)Files compiled!$(RESET)"

re: fclean all

# @if [ ! -f ./include/readline/libreadline.a ]; then 
mlx:
	@echo "$(YELLOW)Checking MLX42...$(RESET)"
	@if [ ! -f $(MLX42) ]; then \
		(cd $(MLX_DIR) && cmake -B build/); \
		(make -C $(BUILD_DIR)); \
		fi
	@echo "$(YELLOW)MLX42 built!$(RESET)"

dep:
	@echo "$(YELLOW)Checking dependencies...$(RESET)"
	ifeq ($(NOTMAC), 0)
		@if [ ! -f $(BREW)]; then \
			/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" \
			fi
		@if [ ! -f $(CMAKE)]; then \
			brew install cmake \
			fi
		@if [ ! -f $(GLFW)]; then \
			brew install glfw \
			fi
		@echo "$(YELLOW)Dependencies installed!$(RESET)"
	endif

lib: 
	@make -C $(LIB_DIR)

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)
	make clean -C $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BUILD_DIR)
	make fclean -C $(LIB_DIR)

valgrind: 
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./$(NAME)

.PHONY: re debug fclean clean all run mlx dep valgrind