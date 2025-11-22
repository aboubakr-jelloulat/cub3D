NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = src
PARSING_DIR = $(SRC_DIR)/parsing
RAYCASTING_DIR = $(SRC_DIR)/raycasting
RENDER_DIR = $(SRC_DIR)/render
GNL_DIR = shared/gnl
LIBFT_DIR = shared/libft
MLX42_DIR = /Users/$(USER)/MLX42

SRCS = $(SRC_DIR)/main.c  $(PARSING_DIR)/config_key.c $(PARSING_DIR)/file_validator.c $(PARSING_DIR)/garbage_collection.c \
       $(PARSING_DIR)/gc_utils.c $(PARSING_DIR)/init_map.c $(PARSING_DIR)/is_valid_map.c $(PARSING_DIR)/is_valid_map_tile_enclosed.c \
       $(PARSING_DIR)/parse_colors.c $(PARSING_DIR)/parse_game_settings.c $(PARSING_DIR)/parse_map.c $(PARSING_DIR)/parse_textures.c \
       $(PARSING_DIR)/player_setup.c $(PARSING_DIR)/shared.c \
       $(PARSING_DIR)/utils.c $(RAYCASTING_DIR)/draw.c $(RAYCASTING_DIR)/hooks.c $(RAYCASTING_DIR)/player.c $(RAYCASTING_DIR)/raycast.c \
       $(RENDER_DIR)/render_textures.c $(RENDER_DIR)/render_utils.c $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I includes -I $(LIBFT_DIR) -I $(GNL_DIR) -I $(MLX42_DIR)/include

GLFW_PREFIX = $(shell brew --prefix glfw)

LIBS = -L $(LIBFT_DIR) -lft \
       $(MLX42_DIR)/build/libmlx42.a \
       -L $(GLFW_PREFIX)/lib -lglfw -lm \
       -framework OpenGL -framework Cocoa -framework IOKit -framework CoreFoundation

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@printf "\n$(NAME) compiled successfully! \n"


%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@make -C $(LIBFT_DIR) clean
	@printf "$(RED)Removing object files$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

cub : all clean

.PHONY: all clean fclean re