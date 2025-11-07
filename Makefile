NAME		= cub3D


# Directories
SRC_DIR		= src
INCLUDE_DIR	= includes
SHARED_DIR	= shared

# Sub-directories
PARSING_DIR		= $(SRC_DIR)/parsing
RAYCASTING_DIR	= $(SRC_DIR)/raycasting
RENDER_DIR		= $(SRC_DIR)/render
GNL_DIR			= $(SHARED_DIR)/gnl
LIBFT_DIR		= $(SHARED_DIR)/libft

# Source files
MAIN_SRC		= $(SRC_DIR)/main.c
PARSING_SRCS	= $(wildcard $(PARSING_DIR)/*.c)
RAYCASTING_SRCS	= $(wildcard $(RAYCASTING_DIR)/*.c)
RENDER_SRCS		= $(wildcard $(RENDER_DIR)/*.c)
GNL_SRCS		= $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

# All source files
SRCS		= $(MAIN_SRC) $(PARSING_SRCS) $(RAYCASTING_SRCS) $(RENDER_SRCS) $(GNL_SRCS)

# Object files
OBJS		= $(SRCS:.c=.o)

# Headers
HEADERS		= $(wildcard $(INCLUDE_DIR)/*.h)

# Libraries
LIBFT		= $(LIBFT_DIR)/libft.a


# Compiler and flags 
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -ffast-math -O3 
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX)

#mlx
MLX = ~Desktop/MLX42

MLX42_DIR = /Users/${USER}/MLX42

INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX42_DIR)/include


# LIBS = -L$(LIBFT_DIR) -lft $(MLX42_DIR)/build/libmlx42.a \
#        -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation \
#        -L"/Users/${USER}/goinfre/homebrew/Cellar/glfw/3.4/lib" -lglfw -lm

GLFW_PREFIX  := $(shell brew --prefix glfw)
GLFW_LIB_DIR := $(GLFW_PREFIX)/lib
GLFW_INC_DIR := $(GLFW_PREFIX)/include

LIBS = -L$(LIBFT_DIR) -lft \
       $(MLX42_DIR)/build/libmlx42.a \
       -L$(GLFW_LIB_DIR) -lglfw3 -lm \
       -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation



all: $(NAME)

$(LIBFT):
	@make -C ./shared/libft

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "$(CYAN)\n$(NAME) compiled successfully! ✅$(RESET)\n"

%.o: %.c $(HEADERS)
	@printf "$(CYAN)Compiling $<$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@printf "$(RED)Removing object files$(RESET)\n"
	@rm -f $(OBJS)
	@make -C ./shared/libft clean

fclean: clean
	@printf "$(RED)Removing $(NAME)$(RESET)\n"
	@rm -f $(NAME)
	@make -C ./shared/libft fclean

re: fclean all

cub : all clean

.PHONY: all clean fclean re


RESET		= \033[0m
RED			= \033[31m
CYAN		= \033[36m