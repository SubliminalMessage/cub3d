/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:00:29 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:14:10 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

void	draw_minimap_player(t_game *game)
{
	int			i;
	int			j;
	t_img		*img;
	t_player	*player;

	img = &game->canvas;
	player = &game->player;
	i = -(PLAYER_MINIMAP_SIZE / 2);
	while (i < (PLAYER_MINIMAP_SIZE / 2))
	{
		j = -(PLAYER_MINIMAP_SIZE / 2);
		while (j < (PLAYER_MINIMAP_SIZE / 2))
		{
			place_pixel_at(img, point(player->x * MP_CELL_SZ + i + 16,
					player->y * MP_CELL_SZ + j + 16), 0x840032);
			j++;
		}
		i++;
	}
}

void	draw_minimap_background(t_game *game)
{
	int	x;
	int	y;

	draw_square(game, point(8, 8), size(8 * (game->map_width + 2),
			8 * (game->map_height + 2)), 0x7180AC);
	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_square(game, point(8 * (x + 2),
						8 * (y + 2)), size(8, 8), 0x2B4570);
			else if (game->map[y][x] == '0')
				draw_square(game, point(8 * (x + 2),
						8 * (y + 2)), size(8, 8), 0x002642);
			x++;
		}
		y++;
	}
}

void	draw_minimap_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '1')
				draw_square(game, point(8 * (x + 2),
						8 * (y + 2)), size(8, 8), 0x2B4570);
			x++;
		}
		y++;
	}
}

void	draw_square(t_game *game, t_point p, t_size s, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < s.h)
	{
		x = 0;
		while (x < s.w)
		{
			place_pixel_at(&game->canvas, point(p.x + x, p.y + y), color);
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;
	int	color;

	color = game->ceil_color;
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		if (y > W_HEIGHT / 2)
			color = game->floor_color;
		while (x < W_WIDTH)
		{
			place_pixel_at(&game->canvas, point(x, y), color);
			x++;
		}
		y++;
	}
}
