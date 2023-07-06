/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:10:13 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:07:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

int	game_loop(t_game *game)
{
	int	i;
	int	total_rays;
	int	count;

	draw_background(game);
	update_player_position(game);
	total_rays = FOV * FOV_DENSITY;
	i = -(total_rays / 2);
	count = 0;
	while (i < (total_rays / 2))
	{
		draw_ray(game, game->player.angle + (i * RAY_STEP), count);
		i++;
		count++;
	}
	mlx_put_image_to_window(game->mlx, game->window, game->canvas.img, 0, 0);
	return (0);
}

void	transpile(t_filecontent *map_file, t_game *game)
{
	game->north_texture = new_texture(game, map_file->texture[0], 32, 32);
	game->south_texture = new_texture(game, map_file->texture[1], 32, 32);
	game->west_texture = new_texture(game, map_file->texture[2], 32, 32);
	game->east_texture = new_texture(game, map_file->texture[3], 32, 32);
	game->map_height = map_file->y;
	game->map_width = map_file->x;
	game->player.x = map_file->player_x;
	game->player.y = map_file->player_y;
	game->player.angle = map_file->player_o;
	game->map = map_file->map.items;
	game->map[(int)(game->player.y)][(int)(game->player.x)] = '0';
	game->floor_color = rgb_to_hex(map_file->f[0],
			map_file->f[1], map_file->f[2]);
	game->ceil_color = rgb_to_hex(map_file->c[0],
			map_file->c[1], map_file->c[2]);
}

int	main(int argc, char **argv)
{
	t_filecontent	map_file;
	t_game			game;

	if (argc != 2)
	{
		printf("Usage: ./cub3D <mapfile.cub>\n");
		close_window(NULL);
	}
	if (!start_parseo(&map_file, argv[1]))
		close_window(NULL);
	game = init_game_structure();
	transpile(&map_file, &game);
	rotate_player(&game, 0.001);
	mlx_hook(game.window, ON_KEYDOWN, 0, handle_input_down, &game);
	mlx_hook(game.window, ON_KEYUP, 0, handle_input_up, &game);
	mlx_hook(game.window, 17, 1L < 17, close_window, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
}
