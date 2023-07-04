/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/04 19:12:23 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

void transpile(t_fileContent *map_file, t_game *game)
{
	game->debug_texture = new_texture(game, "./assets/debug.xpm", 32, 32); // Remove this
	game->north_texture = new_texture(game, map_file->texture[0], 32, 32);
	game->south_texture = new_texture(game,  map_file->texture[1], 32, 32);
	game->west_texture = new_texture(game, map_file->texture[2], 32, 32);
	game->east_texture = new_texture(game,  map_file->texture[3], 32, 32);
	game->map_height = map_file->Y;
	game->map_width = map_file->X;
	game->player.x = map_file->player_x;
	game->player.y = map_file->player_y;
	game->player.angle = map_file->player_o;
	game->map = map_file->map.items;
	game->map[(int)(game->player.y)][(int)(game->player.x)] = '0';
	game->floor_color = rgb_to_hex(map_file->F[0], map_file->F[1], map_file->F[2]);
	game->ceil_color = rgb_to_hex(map_file->C[0], map_file->C[1], map_file->C[2]);
}

int main(int argc, char **argv)
{
	t_fileContent map_file;
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: ./cub3D <mapfile.cub>\n");
		close_window(NULL);
	}
	if (!start_parseo(&map_file, argv[1]))
		close_window(NULL);
	game = init_game_structure();
	transpile(&map_file, &game);
	mlx_hook(game.window, ON_KEYDOWN, 0, handle_input_down, &game);
	mlx_hook(game.window, ON_KEYUP, 0, handle_input_up, &game);
	mlx_hook(game.window, 17, 1L < 17, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_hook(game.window, ON_MOUSEMOVE, 0, handle_mouse_move, &game);
	mlx_loop(game.mlx);
}
