/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:44:15 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/04 18:30:58 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	rotate_player(t_game *game, float angle)
{
	game->player.angle += angle;
	if (game->player.angle < 0)
		game->player.angle += 2 * PI;
	if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
	game->player.dx = cos(game->player.angle) * PLAYER_STEP;
	game->player.dy = sin(game->player.angle) * PLAYER_STEP;
}

static void	move_player(t_game *game, float dx, float dy)
{
	float	multiplier;
	float	final_x;
	float	final_y;

	multiplier = 1;
	final_x = game->player.x + dx * multiplier;
	final_y = game->player.y + dy * multiplier;
	/*
	// Collisions for mandatory part (can get through walls, but can't get outside map)
	if (final_x >= 0 && final_x < game->map_width)
		game->player.x += dx;
	if (final_y >= 0 && final_y < game->map_height)
		game->player.y += dy;
	*/
	// Collisions for Bonus Part (can't get through any wall)
	if (game->map[(int)floor(game->player.y)][(int)final_x] == '0')
		game->player.x += dx;
	if (game->map[(int)final_y][(int)floor(game->player.x)] == '0')
		game->player.y += dy;
}

void	update_player_position(t_game *game)
{
	if (game->player.keys.w_pressed)
		move_player(game, game->player.dx, game->player.dy);
	if (game->player.keys.s_pressed)
		move_player(game, -game->player.dx, -game->player.dy);
	if (game->player.keys.a_pressed)
		move_player(game, game->player.dy, -game->player.dx);
	if (game->player.keys.d_pressed)
		move_player(game, -game->player.dy, game->player.dx);
	if (game->player.keys.left_pressed)
		rotate_player(game, -PLAYER_ROTATION);
	if (game->player.keys.right_pressed)
		rotate_player(game, PLAYER_ROTATION);
}
