/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/11 14:45:27 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap(t_game *game);

int mapX = 8;
int mapY = 8;
int mapS = 64;
char *raw_map = "11111111\n10100101\n10100011\n10000001\n10101001\n10101001\n10001011\n11111111"; // With walls
//char *raw_map = "11111111\n10000001\n10000001\n10000001\n10000001\n10000001\n10000001\n11111111"; // Without walls

void	draw_minimap_player(t_game *game)
{
	int	i;
	int	j;
	t_img *img;
	t_player *player;

	img = &game->canvas;
	player = &game->player;
	i = 0;
	while (i < PLAYER_MINIMAP_SIZE)
	{
		j = 0;
		while (j < PLAYER_MINIMAP_SIZE)
		{
			place_pixel_at(img, point(player->x * MINIMAP_CELL_SIZE + i, player->y * MINIMAP_CELL_SIZE + j), size(W_WIDTH, W_HEIGHT), 0xFCCE00);
			j++;
		}
		i++;
	}
	int x1 = player->x * MINIMAP_CELL_SIZE + (PLAYER_MINIMAP_SIZE / 2);
	int y1 = player->y * MINIMAP_CELL_SIZE + (PLAYER_MINIMAP_SIZE / 2);
	draw_line(img, point(x1, y1), point(x1 + player->dx * 5000, y1 + player->dy * 5000), 0x3002CE);
}

void	update_player_position(t_game *game)
{
	if (game->player.w_pressed)
	{
		game->player.x += game->player.dx;
		game->player.y += game->player.dy;
	}
	if (game->player.s_pressed)
	{
		game->player.x -= game->player.dx;
		game->player.y -= game->player.dy;
	}
	if (game->player.a_pressed)
	{
		game->player.angle -= PLAYER_ROTATION;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.dx = cos(game->player.angle) * PLAYER_STEP;
		game->player.dy = sin(game->player.angle) * PLAYER_STEP;
	}
	if (game->player.d_pressed)
	{
		game->player.angle += PLAYER_ROTATION;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.dx = cos(game->player.angle) * PLAYER_STEP;
		game->player.dy = sin(game->player.angle) * PLAYER_STEP; // This two lines are shared between 'A' and 'D'.
	}
}


int	game_loop(t_game *game)
{
	int i;
	int total_rays;

	fill_image(&game->canvas, 0x3D3D3D, size(W_WIDTH, W_HEIGHT));
	update_player_position(game);

	total_rays = FOV * FOV_DENSITY;
	i = -(total_rays / 2);
	int count = 0;
	while (i < (total_rays / 2))
	{
		draw_ray(game, game->player.angle + (i * RAY_STEP), count);
		i++;
		count++;
	}

	draw_minimap(game);
	draw_minimap_player(game);

	mlx_put_image_to_window(game->mlx, game->window, game->canvas.img, 0, 0);
	return (0);
}

void	draw_minimap(t_game *game)
{
	int color;

	int y = 0;
	while (y < mapY)
	{
		int x = 0;
		while (x < mapX)
		{
			if (game->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x0F0F0F;
			int xo = x * MINIMAP_CELL_SIZE;
			int yo = y * MINIMAP_CELL_SIZE;
			int i = 1;
			while (i < MINIMAP_CELL_SIZE - 1)
			{
				int j = 1;
				while (j < MINIMAP_CELL_SIZE - 1)
				{
					place_pixel_at(&game->canvas, point(xo + j, yo + i), size(W_WIDTH, W_HEIGHT), color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}

}

int main(void)
{
	t_game	game;

	game = init_game_structure();

	game.map_height = 8;
	game.map_width = 8;
	game.map = ft_split(raw_map, '\n');
	int i = 0;
	while (i < 8)
	{
		printf("%s\n", game.map[i]);
		i++;
	}
	mlx_hook(game.window, ON_KEYDOWN, 0, handle_input_down, &game);
	mlx_hook(game.window, ON_KEYUP, 0, handle_input_up, &game);
	mlx_hook(game.window, 17, 1L < 17, close_window, NULL);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
