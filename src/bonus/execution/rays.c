/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:07:06 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/11 22:43:30 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	draw_ray(t_game *game, float angle, int count)
{
	t_ray collision_ray;
	t_point	player;
	t_point	collision;

	angle -= 0.01;
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

	float px_per_ray = (float)W_WIDTH / (float)(FOV * FOV_DENSITY);
	float ray_angle = game->player.angle - collision_ray.angle;
	float correct_distance = collision_ray.distance * cos(ray_angle);
	int wall_height = 32 * 20;
	float projected_height = wall_height / correct_distance;
	if (projected_height > W_HEIGHT)
		projected_height = W_HEIGHT;

	float  img_x = 0;
	int img_size = 32;
	if (collision_ray.collision_side == NORTH || collision_ray.collision_side == SOUTH)
		img_x = collision_ray.x - floor(collision_ray.x);
	if (collision_ray.collision_side == EAST || collision_ray.collision_side == WEST)
		img_x = collision_ray.y - floor(collision_ray.y);

	img_x = floor(img_x * img_size);
	int image_x = (int) img_x;

	int color = 0x000000;
	if (collision_ray.collision_side == NORTH)
	{
		color = 0x095256;
		if (image_x % 2 == 0)
			color = 0x052C2E;
	}
	if (collision_ray.collision_side == SOUTH)
	{
		color = 0x087F8C;
		if (image_x % 2 == 0)
			color = 0x033338;
	}
	if (collision_ray.collision_side == EAST)
	{
		color = 0x5AAA95;
		if (image_x % 2 == 0)
			color = 0x2A4F45;
	}
	if (collision_ray.collision_side == WEST)
	{
		color = 0x86A873;
		if (image_x % 2 == 0)
			color = 0x48593E;
	}

	int i = 0;
	while (i < px_per_ray)
	{
		t_point start = point(ceil(count * px_per_ray) + i, (W_HEIGHT / 2) - (projected_height / 2));
		t_point end = point(ceil(count * px_per_ray) + i, (W_HEIGHT / 2) + (projected_height / 2));
		int j = start.y;
		while (j < end.y)
		{
			place_pixel_at(&game->canvas, point(start.x, j), size(W_WIDTH, W_HEIGHT), color);
			j++;
		}
		i++;
	}

}
