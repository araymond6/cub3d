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

SRCS = main.c parsing.c
VPATH = $(SRC_DIR) $(INC_DIR)

OBJS = $(SRCS:%.c=%.o)
OBJ_PRE = $(addprefix $(OBJ_DIR), $(OBJS))

INC = cub.h
INC_PRE = $(addprefix $(INC_DIR), $(INC))

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

mlx:
	(cd $(MLX_DIR) && cmake -B build/)
	(make -C $(BUILD_DIR))

dep:
	# @if [ ! -f /Users/$(USER)/.brew/bin/brew]; then \
	# 	/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)" \
	# 	fi
	# @if [ ! -f /Users/$(USER)/.brew/bin/cmake]; then \
	# 	brew install cmake \
	# 	fi
	# @if [ ! -f /Users/$(USER)/.brew/Cellar/glfw]; then \
	# 	brew install glfw \
	# 	fi

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