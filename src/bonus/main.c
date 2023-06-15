/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/15 16:08:01 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_minimap_background(t_game *game);
void	draw_minimap_walls(t_game *game);

int mapX = 8;
int mapY = 8;
int mapS = 64;
//char *raw_map = "11111111\n10100101\n10100011\n10000001\n10101001\n10101001\n10001011\n11111111"; // With walls
//char *raw_map = "11111111\n10000001\n10000001\n10000001\n10010001\n10000001\n10000001\n11111111"; // Without walls
// Subject Map:
char *raw_map = "        1111111111111111111111111\n        1000000000110000000000001\n        1011000001110000000000001\n        1001000000000000000000001\n111111111011000001110000000000001\n100000000011000001110111111011111\n11110111111111011100000010001    \n11110111111111011101010010001    \n11000000110101011100000000001    \n10000000000000001100000010001    \n10000000000000001101010010001    \n1100000111010101111101111000111  \n11110111 1110101 101111010001    \n11111111 1111111 111111111111    \n";
// Height: 14 ; Width: 33

#define SKY_COLOR 0x3D3D3D // TODO: Read this values from 'game'.
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
			place_pixel_at(&game->canvas, point(x, y), color);
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
	draw_minimap_background(game);
	total_rays = FOV * FOV_DENSITY;
	i = -(total_rays / 2);
	int count = 0;
	while (i < (total_rays / 2))
	{
		draw_ray(game, game->player.angle + (i * RAY_STEP), count);
		i++;
		count++;
	}
	draw_minimap_walls(game);
	draw_minimap_player(game);
	mlx_put_image_to_window(game->mlx, game->window, game->canvas.img, 0, 0);
	return (0);
}

int main(void)
{
	t_game	game;
	int i = 0;

	game = init_game_structure(); // Init struct
	// Add textures manually
	game.debug_texture = new_texture(&game, "./assets/debug.xpm", 32, 32);
	game.north_texture = new_texture(&game, "./assets/arrow_n.xpm", 32, 32);
	game.south_texture = new_texture(&game, "./assets/arrow_s.xpm", 32, 32);
	game.east_texture = new_texture(&game, "./assets/arrow_e.xpm", 32, 32);
	game.west_texture = new_texture(&game, "./assets/arrow_w.xpm", 32, 32);

	// Add map & player coords manually
	game.map = ft_split(raw_map, '\n');
	game.map_height = 14;
	game.map_width = 33;
	game.player.x = 25.5f;
	game.player.y = 2.5f;

	// Print map. TODO: Remove this lol
	while (i < game.map_height)
	{
		printf("%s\n", game.map[i]);
		i++;
	}

	// Start the game loop & stuff
	mlx_hook(game.window, ON_KEYDOWN, 0, handle_input_down, &game);
	mlx_hook(game.window, ON_KEYUP, 0, handle_input_up, &game);
	mlx_hook(game.window, 17, 1L < 17, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
