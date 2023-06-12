### ---   ---   ---         ---   ---   --- ###
#             PROJECT COMPILATION             #
### ---   ---   ---         ---   ---   --- ###

CC	= gcc
CFLAGS	= -Wall -Werror -Wextra -g3 -fsanitize=address
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

SRC_BONUS	=	src/bonus/main.c \
				src/bonus/execution/setup.c \
				src/bonus/execution/hooks.c \
				src/bonus/execution/rays.c \
				src/bonus/utils/math_utils.c \
				src/bonus/utils/mlx_utils.c \
				src/bonus/utils/rays_utils.c

SRC_OBJS 	= $(SRC_BONUS:src/%.c=bin/%.o)

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

$(NAME): $(MLX) $(LIBFT) $(SRC_OBJS)
	@$(CC) $(CFLAGS) $(SRC_OBJS) $(LIBFT) $(MLX_FLAGS) -I $(INCS_PATH) -I $(LIBFT_PATH) -I mlx/ -o $(NAME)

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
