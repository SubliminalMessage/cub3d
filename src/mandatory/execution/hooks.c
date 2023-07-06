/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:26:29 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:26:01 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_game *game)
{
	(void) game;
	exit(0);
	return (0);
}

int	handle_input_down(int key_code, t_game *game)
{
	if (key_code == W_KEY)
		game->player.keys.w_pressed = true;
	if (key_code == A_KEY)
		game->player.keys.a_pressed = true;
	if (key_code == S_KEY)
		game->player.keys.s_pressed = true;
	if (key_code == D_KEY)
		game->player.keys.d_pressed = true;
	if (key_code == LEFT_KEY)
		game->player.keys.left_pressed = true;
	if (key_code == RIGHT_KEY)
		game->player.keys.right_pressed = true;
	if (key_code == SPACE_KEY)
		game->player.keys.space_pressed = true;
	if (key_code == ESC_KEY)
		close_window(game);
	return (0);
}

int	handle_input_up(int key_code, t_game *game)
{
	if (key_code == W_KEY)
		game->player.keys.w_pressed = false;
	if (key_code == A_KEY)
		game->player.keys.a_pressed = false;
	if (key_code == S_KEY)
		game->player.keys.s_pressed = false;
	if (key_code == D_KEY)
		game->player.keys.d_pressed = false;
	if (key_code == LEFT_KEY)
		game->player.keys.left_pressed = false;
	if (key_code == RIGHT_KEY)
		game->player.keys.right_pressed = false;
	if (key_code == SPACE_KEY)
		game->player.keys.space_pressed = false;
	return (0);
}
