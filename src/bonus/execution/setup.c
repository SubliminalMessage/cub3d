/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:09 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/09 23:47:51 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_game	init_game_structure(void)
{
	t_game	game;

	// MLX Setup
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, W_WIDTH, W_HEIGHT, "Cub3D");
	game.canvas = new_image(game.mlx, W_WIDTH, W_HEIGHT);

	// Player Setup
	game.player.x = 4 * MINIMAP_CELL_SIZE;
	game.player.y = 2 * MINIMAP_CELL_SIZE;
	game.player.angle = 90;
	game.player.w_pressed = false;
	game.player.a_pressed = false;
	game.player.s_pressed = false;
	game.player.d_pressed = false;
	game.player.dx = cos(game.player.angle) * PLAYER_STEP;
	game.player.dy = sin(game.player.angle) * PLAYER_STEP;

	return (game);
}
