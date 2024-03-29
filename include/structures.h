/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:56:48 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 21:02:26 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef enum e_bool
{
	false,
	true
}				t_bool;

typedef struct s_point
{
	float		x;
	float		y;
}				t_point;

typedef struct s_size
{
	float		w;
	float		h;
}				t_size;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	t_size		size;
}				t_img;

typedef struct t_keys
{
	t_bool		w_pressed;
	t_bool		a_pressed;
	t_bool		s_pressed;
	t_bool		d_pressed;
	t_bool		left_pressed;
	t_bool		right_pressed;
	t_bool		space_pressed;
}				t_keys;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	angle;
	t_keys	keys;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
	t_player	player;
	t_img		canvas;
	int			map_width;
	int			map_height;
	char		**map;
	t_img		north_texture;
	t_img		south_texture;
	t_img		east_texture;
	t_img		west_texture;
	int			floor_color;
	int			ceil_color;
}				t_game;

typedef enum e_side
{
	NONE,
	NORTH,
	SOUTH,
	EAST,
	WEST
}				t_side;

typedef struct s_ray
{
	float		x;
	float		y;
	float		angle;
	float		x_near;
	float		y_near;
	float		x_offset;
	float		y_offset;
	float		distance;
	float		real_height;
	float		projected_height;
	int			box_x;
	t_side		collision_side;
}				t_ray;

typedef struct s_arraylist
{
	char		**items;
	int			capacity;
	int			size;
}				t_arraylist;

typedef struct s_filecontent
{
	int			x;
	int			y;
	char		*texture[4];
	int			f[3];
	int			c[3];
	t_arraylist	map;
	float		player_x;
	float		player_y;
	float		player_o;

}				t_filecontent;

#endif
