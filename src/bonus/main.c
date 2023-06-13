/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/13 16:46:41 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap(t_game *game);

int mapX = 8;
int mapY = 8;
int mapS = 64;
char *raw_map = "11111111\n10100101\n10100011\n10000001\n10101001\n10101001\n10001011\n11111111"; // With walls
//char *raw_map = "11111111\n10000001\n10000001\n10000001\n10010001\n10000001\n10000001\n11111111"; // Without walls

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




#define SKY_COLOR 0x3D3D3D
#define FLOOR_COLOR 0xBB9F06
void	draw_background(t_game *game)
{
	int x;
	int y;
	int color;

	color = SKY_COLOR;
	y = 0;
	while (y < W_HEIGHT)
	{
		x = 0;
		if (y > W_HEIGHT / 2)
			color = FLOOR_COLOR;
		while (x < W_WIDTH)
		{
			place_pixel_at(&game->canvas, point(x, y), size(W_WIDTH, W_HEIGHT), color);
			x++;
		}
		y++;
	}
}

int	game_loop(t_game *game)
{
	int i;
	int total_rays;

	draw_background(game);
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
			if (x == floor(game->player.x) && y == floor(game->player.y))
				color = 0x424242;
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
	int img_size = 32;
	void *texture = mlx_xpm_file_to_image(game.mlx, "./assets/arrow.xpm", &img_size, &img_size);
	if (!texture)
	{
		printf("Texture failed\n");
		exit(1);
	}
	t_img game_texture;
	game_texture.img = texture;
	game_texture.addr = mlx_get_data_addr(game_texture.img, &game_texture.bits_per_pixel, &game_texture.line_length, &game_texture.endian);


	game.texture = game_texture;
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
	mlx_hook(game.window, 17, 1L < 17, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
