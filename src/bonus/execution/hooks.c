/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:26:29 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/12 17:12:38 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	close_window(t_game *game)
{
	int i = 0;
	while (game->map[i])
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	exit(0);
	return (0);
}

int	handle_input_down(int key_code, t_game *game)
{
	if (key_code == W_KEY)
		game->player.w_pressed = true;
	if (key_code == A_KEY)
		game->player.a_pressed = true;
	if (key_code == S_KEY)
		game->player.s_pressed = true;
	if (key_code == D_KEY)
		game->player.d_pressed = true;
	if (key_code == ESC_KEY)
		close_window(game);
	return (0);
}

int	handle_input_up(int key_code, t_game *game)
{
	if (key_code == W_KEY)
		game->player.w_pressed = false;
	if (key_code == A_KEY)
		game->player.a_pressed = false;
	if (key_code == S_KEY)
		game->player.s_pressed = false;
	if (key_code == D_KEY)
		game->player.d_pressed = false;
	return (0);
}
