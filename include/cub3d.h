/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:51 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/11 14:16:25 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <libft.h>
#include <mlx.h>
#include <stdio.h>
#include <math.h>

#define W_WIDTH 1200 // Map Size
#define W_HEIGHT (int) (W_WIDTH / 16) * 9 // 16:9 Aspect Ratio

#define PI 3.1415926 // Math values

#define MINIMAP_CELL_SIZE 32 // Minimap settings
#define PLAYER_STEP 0.05
#define PLAYER_ROTATION 0.05
#define PLAYER_MINIMAP_SIZE 4

#define W_KEY 13 // MLX Key Codes
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define ESC_KEY 53
#define ON_KEYDOWN 2 // MLX Event Hooks
#define ON_KEYUP 3
#define DIR_HORIZONTAL 'H' // Rays settings
#define DIR_VERTICAL 'V'

// Raycasting settings
#define FOV 30 // Degrees of Field of Vision
#define FOV_DENSITY 10 // How many rays per degree
#define ONE_DEGREE 0.0174533 // One degree in radians
#define RAY_STEP ONE_DEGREE / FOV_DENSITY // How much each ray is separated from the next

typedef enum { false, true } t_bool;

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_player
{
	float	x; // Position
	float	y; // Position
	float	dx; // delta X
	float	dy; // Delta Y
	float	angle;
	t_bool	w_pressed;
	t_bool	a_pressed;
	t_bool	s_pressed;
	t_bool	d_pressed;
} t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_player	player;
	t_img		canvas;
	int			map_width;
	int			map_height;
	char		**map;
} t_game;

typedef struct s_point
{
	float	x;
	float	y;
} t_point;

typedef struct s_size
{
	float	w;
	float	h;
} t_size;

typedef enum { NONE, NORTH, SOUTH, EAST, WEST } t_side;

typedef struct s_ray
{
	float	x;
	float	y;
	float	angle;
	float	x_near;
	float	y_near;
	float	x_offset;
	float	y_offset;
	float	distance;
	t_side	collision_side;
} t_ray;

// Functions
t_game	init_game_structure(void);
int close_window(void);
int	handle_input_down(int key_code, t_game *game);
int	handle_input_up(int key_code, t_game *game);
int	max(int a, int b);
t_img	new_image(void *mlx, int w, int h);
void	place_pixel_at(t_img *img, t_point point, t_size size, int color);
void	fill_image(t_img *img, int color, t_size img_size);
void	draw_line(t_img *img, t_point a, t_point b, int color);
t_point	point(float x, float y);
t_size size(float w, float h);
t_ray	ray(t_game *game, float angle, char direction);
t_ray min_ray(t_ray a, t_ray b);
void	draw_ray(t_game *game, float angle, int count);

#endif
