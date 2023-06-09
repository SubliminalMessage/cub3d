/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:51 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/09 23:37:56 by dangonza         ###   ########.fr       */
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

#define MINIMAP_CELL_SIZE 50 // Minimap settings
#define PLAYER_STEP 0.15 * MINIMAP_CELL_SIZE / 10
#define PLAYER_MINIMAP_SIZE 4

#define W_KEY 13 // MLX Key Codes
#define A_KEY 0
#define S_KEY 1
#define D_KEY 2
#define ESC_KEY 53
#define ON_KEYDOWN 2 // MLX Event Hooks
#define ON_KEYUP 3

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
} t_game;

// Functions
t_game	init_game_structure(void);
int close_window(void);
int	handle_input_down(int key_code, t_game *game);
int	handle_input_up(int key_code, t_game *game);
int	max(int a, int b);
t_img	new_image(void *mlx, int w, int h);
void	place_pixel_at(t_img *img, int x, int y, int color);
void	fill_image(t_img *img, int color, int sz_x, int sz_y);
void	draw_line(t_img *img, float x1, float y1, float x2, float y2, int color);

#endif
