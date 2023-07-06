### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra #-g3 -fsanitize=address
MLX = mlx/libmlx.a
MLX_FLAGS = $(MLX) -framework OpenGL -framework AppKit

### ---   ---   ---         ---   ---   --- ###
#               PROJECT PATHS                 #
### ---   ---   ---         ---   ---   --- ###

INCS_PATH			= include/
SRCS_PATH			= src/
BIN_PATH			= bin/
LIBFT_PATH			= libft/

### ---   ---   ---         ---   ---   --- ###
#               PROJECT FILES                 #
### ---   ---   ---         ---   ---   --- ###

NAME		= cub3D
LIBFT		= $(LIBFT_PATH)/libft.a

SRC_MAND	=	src/mandatory/main.c \
				src/mandatory/execution/setup.c \
				src/mandatory/execution/hooks.c \
				src/mandatory/execution/rays.c \
				src/mandatory/execution/player_movement.c \
				src/mandatory/utils/math_utils.c \
				src/mandatory/utils/mlx_utils.c \
				src/mandatory/utils/rays_utils.c \
				src/mandatory/utils/arraylist.c \
				src/mandatory/utils/color_utils.c \
				src/mandatory/utils/string_utils.c \
				src/mandatory/utils/map_getters.c \
				src/mandatory/parser/start_parseo.c \
				src/mandatory/parser/parseo.c \
				src/mandatory/parser/parse_utils.c \
				src/mandatory/parser/map_checker.c \
				src/mandatory/parser/parse_textures.c \
				src/mandatory/parser/parse_rgb.c

SRC_BONUS	=	src/bonus/main_bonus.c \
				src/bonus/execution/setup_bonus.c \
				src/bonus/execution/hooks_bonus.c \
				src/bonus/execution/rays_bonus.c \
				src/bonus/execution/player_movement_bonus.c \
				src/bonus/execution/minimap_bonus.c \
				src/bonus/utils/math_utils_bonus.c \
				src/bonus/utils/mlx_utils_bonus.c \
				src/bonus/utils/rays_utils_bonus.c \
				src/bonus/utils/arraylist_bonus.c \
				src/bonus/utils/color_utils_bonus.c \
				src/bonus/utils/string_utils_bonus.c \
				src/bonus/utils/map_getters_bonus.c \
				src/bonus/parser/start_parseo_bonus.c \
				src/bonus/parser/parseo_bonus.c \
				src/bonus/parser/parse_utils_bonus.c \
				src/bonus/parser/map_checker_bonus.c \
				src/bonus/parser/parse_textures_bonus.c \
				src/bonus/parser/parse_rgb_bonus.c

SRC_OBJS_MAND 	= $(SRC_MAND:src/%.c=bin/%.o)
SRC_OBJS_BONUS 	= $(SRC_BONUS:src/%.c=bin/%.o)

### ---   ---   ---         ---   ---   --- ###
#              COLORS & EXTRAS :)             #
### ---   ---   ---         ---   ---   --- ###

RED		= '\033[1;31m'
GREEN	= '\033[1;32m'
PURPLE	= '\033[1;35m'
BLUE	= '\033[1;34m'
RESET	= '\033[0;0m'

### ---   ---   ---         ---   ---   --- ###
#                  GAME RULES                 #
### ---   ---   ---         ---   ---   --- ###

.PHONY: all re clean fclean bonus

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(SRC_OBJS_MAND)
	@$(CC) $(CFLAGS) $(SRC_OBJS_MAND) $(LIBFT) $(MLX_FLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -o $(NAME)

bonus: .bonus

.bonus: $(MLX) $(LIBFT) $(SRC_OBJS_BONUS)
	@touch .bonus
	@$(CC) $(CFLAGS) $(SRC_OBJS_BONUS) $(LIBFT) $(MLX_FLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -o $(NAME)

$(MLX):
	@echo $(PURPLE)"[Make MLX]"$(RESET)
	@make -C mlx/

$(LIBFT):
	@echo $(PURPLE)"[Make Libft]"$(RESET)
	@make -C $(LIBFT_PATH)

	@echo $(PURPLE)"[Make cub3D]"$(RESET)

bin/%.o: src/%.c
	@echo $(BLUE)"Compilation "$(RESET)": $< "
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -c $< -o $@

clean:
	@echo $(RED)"[Deleting Object Files]"$(RESET)
	@rm -rf bin/
	@make clean -C mlx/
	@echo $(RED)"MLX Object Files deleted"$(RESET)
	@rm -f .bonus
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@rm -rf $(NAME) $(MLX)
	@echo $(RED)"$(NAME) deleted"$(RESET)
	@make fclean -C $(LIBFT_PATH)

re: fclean all
