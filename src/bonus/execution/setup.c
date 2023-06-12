/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:19:09 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/13 01:03:15 by dangonza         ###   ########.fr       */
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
	game.player.x = 3.5f;
	game.player.y = 2.5f;
	game.player.angle = PI/2 + 0.001;
	game.player.keys.w_pressed = false;
	game.player.keys.a_pressed = false;
	game.player.keys.s_pressed = false;
	game.player.keys.d_pressed = false;
	game.player.keys.left_pressed = false;
	game.player.keys.right_pressed = false;
	game.player.dx = cos(game.player.angle) * PLAYER_STEP;
	game.player.dy = sin(game.player.angle) * PLAYER_STEP;

	return (game);
}
