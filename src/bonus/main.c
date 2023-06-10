/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/10 15:12:37 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap(t_game *game);

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
			place_pixel_at(img, point(player->x + i, player->y + j), 0xFCCE00);
			j++;
		}
		i++;
	}
	int x1 = player->x + (PLAYER_MINIMAP_SIZE / 2);
	int y1 = player->y + (PLAYER_MINIMAP_SIZE / 2);
	draw_line(img, point(x1, y1), point(x1 + player->dx * 30, y1 + player->dy * 30), 0xFCCE00);
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
		game->player.angle -= 0.025;
		if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		game->player.dx = cos(game->player.angle) * PLAYER_STEP;
		game->player.dy = sin(game->player.angle) * PLAYER_STEP;
	}
	if (game->player.d_pressed)
	{
		game->player.angle += 0.025;
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		game->player.dx = cos(game->player.angle) * PLAYER_STEP;
		game->player.dy = sin(game->player.angle) * PLAYER_STEP; // This two lines are shared between 'A' and 'D'.
	}
}

int	game_loop(t_game *game)
{
	fill_image(&game->canvas, 0x003D3D3D, W_WIDTH, W_HEIGHT);
	update_player_position(game);
	draw_minimap(game);
	draw_minimap_player(game);

	mlx_put_image_to_window(game->mlx, game->window, game->canvas.img, 0, 0);
	return (0);
}

int mapX = 10;
int mapY = 10;
int mapS = 100;
int map[10][10] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 1, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

void	draw_minimap(t_game *game)
{
	int color;

	int y = 0;
	while (y < mapY)
	{
		int x = 0;
		while (x < mapX)
		{
			if (map[y][x] == 1)
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
					place_pixel_at(&game->canvas, point(xo + j, yo + i), color);
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

	mlx_hook(game.window, ON_KEYDOWN, 0, handle_input_down, &game);
	mlx_hook(game.window, ON_KEYUP, 0, handle_input_up, &game);
	mlx_hook(game.window, 17, 1L < 17, close_window, NULL);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
