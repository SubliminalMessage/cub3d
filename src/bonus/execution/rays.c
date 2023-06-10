/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:07:06 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/11 01:13:20 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_ray(t_game *game, float angle)
{
	t_ray collision_ray;
	t_point	player;
	t_point	collision;

	if (angle < 0)
		angle += PI * 2;
	if (angle > PI * 2)
		angle -= PI * 2;
	collision_ray = min_ray(ray(game, angle, 'H'), ray(game, angle, 'V'));
	// Draw the Minimap //
	player = point(game->player.x * MINIMAP_CELL_SIZE + 2, game->player.y * MINIMAP_CELL_SIZE + 2);
	collision = point(collision_ray.x * MINIMAP_CELL_SIZE, collision_ray.y * MINIMAP_CELL_SIZE);
	draw_line(&game->canvas, player, collision, 0x33F0FF);
	/////////////////////
}
