/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:51 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/04 19:44:49 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <libft.h>
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include <structures.h>
# include <fcntl.h>

# define W_WIDTH 1200 // Map Size
# define TEST W_WIDTH / 16 // TODO: Too many values on define (AKA: Hardcode this)
# define W_HEIGHT TEST * 9 // 16:9 Aspect Ratio

# define MAX_INT 2147483647

# define PI 3.1415926 // Math values

# define MP_CELL_SZ 8 // Minimap settings
# define PLAYER_MINIMAP_SIZE 4

# define PLAYER_STEP 0.1 // Player Movement Settings
# define PLAYER_ROTATION 0.1

# define W_KEY 13 // MLX Key Codes
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define ESC_KEY 53
# define SPACE_KEY 49

# define ON_KEYDOWN 2 // MLX Event Hooks
# define ON_KEYUP 3
# define ON_MOUSEMOVE 6

# define DIR_HORIZONTAL 'H' // Rays settings
# define DIR_VERTICAL 'V'

// Raycasting settings
# define FOV 60 // Degrees of Field of Vision
# define FOV_DENSITY 10 // How many rays per degree
# define ONE_DEGREE 0.0174533 // One degree in radians
# define RAY_STEP 0.00174533//ONE_DEGREE / FOV_DENSITY // How much each ray is separated from the next

// Functions
t_game	init_game_structure(void);
int		close_window(t_game *game);
int		handle_input_down(int key_code, t_game *game);
int		handle_input_up(int key_code, t_game *game);
int		max(int a, int b);
t_img	new_image(t_game *game, int w, int h);
void	place_pixel_at(t_img *img, t_point point, int color);
void	draw_line(t_img *img, t_point a, t_point b, int color);
t_point	point(float x, float y);
t_size	size(float w, float h);
t_ray	ray(t_game *game, float angle, char direction);
t_ray	min_ray(t_ray a, t_ray b);
void	draw_ray(t_game *game, float angle, int count);
void	update_player_position(t_game *game);
void	rotate_player(t_game *game, float angle);
t_img	new_texture(t_game *game, char *path, int width, int height);
void	draw_minimap_player(t_game *game);
void	draw_minimap_background(t_game *game);
void	draw_minimap_walls(t_game *game);
void	draw_background(t_game *game);
void	draw_square(t_game *game, t_point p, t_size s, int color);
int		rgb_to_hex(int r, int g, int b);
int	handle_mouse_move(int x, int y, t_game *game); // Bonus

// Parse
void arr_init(t_arrayList *list);
void arr_add(t_arrayList *list, char *item);
void arr_clear(t_arrayList *list);
int	map_checker(t_arrayList list);
int map_checker_r(t_arrayList list);
int isRGB(int* n);
int isTexture(char** path);
int fileExist(char* path);
int extenChecker(char* filename, char* extension);
void removeNewLine(char *str);
int check_comas_dig(char *str);
char* appendChar(char* str, char c);
int setCF(char *str, t_fileContent *game, int n);
int parse_CF(char* line , t_fileContent *game);
int parse_textures(char* line , t_fileContent *game);
int vars_parse(char* line , t_fileContent *game);
int read_file(char* argv,t_arrayList* lst,t_fileContent *game_data);
void struct_game_init_textures(t_fileContent *game_data);
void game_data_clear(t_fileContent *game_data);
int start_parseo(t_fileContent *game_data, char* argv);

#endif
