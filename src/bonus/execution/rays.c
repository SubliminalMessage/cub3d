/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:07:06 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/12 18:22:02 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_color_from_image(t_img *img, int x, int y)
{
	char	*dst;
	int	length;
	int	bpp;

	length = img->line_length;
	bpp = img->bits_per_pixel;
	dst = img->addr + (y * length + x * (bpp / 8));
	return (*(unsigned int*)dst);
}

void	draw_ray_line(t_game *game, t_ray ray, int screen_x)
{
	float	vertical_offset;
	int		px;

	vertical_offset = (ray.real_height - ray.projected_height) / 2;
	px = 0;
	while (px < ray.projected_height)
	{
		int pixel_y = px + vertical_offset;

		int box_y = floor(32 * (pixel_y / ray.real_height));
		int box_x = ray.box_x;
		int color = get_color_from_image(&game->texture, box_x, box_y);
		int screen_y = ((W_HEIGHT / 2) - (ray.projected_height / 2)) + px;
		place_pixel_at(&game->canvas, point(screen_x, screen_y), size(W_WIDTH, W_HEIGHT), color);

		px++;
	}
}

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

	// Get Real & Projected Heights
	float px_per_ray = (float)W_WIDTH / (float)(FOV * FOV_DENSITY);
	float ray_angle = game->player.angle - collision_ray.angle;
	float correct_distance = collision_ray.distance * cos(ray_angle);
	int wall_height = 32 * 20;
	collision_ray.real_height = wall_height / correct_distance;
	collision_ray.projected_height = collision_ray.real_height;
	if (collision_ray.projected_height > W_HEIGHT)
		collision_ray.projected_height = W_HEIGHT;

	float  img_x = 0;
	int img_size = 32;
	// Get Box X
	if (collision_ray.collision_side == NORTH || collision_ray.collision_side == SOUTH)
		img_x = collision_ray.x - floor(collision_ray.x);
	if (collision_ray.collision_side == EAST || collision_ray.collision_side == WEST)
		img_x = collision_ray.y - floor(collision_ray.y);

	img_x = floor(img_x * img_size);
	collision_ray.box_x  = (int) img_x;


	int i = 0;
	while (i < px_per_ray)
	{
		draw_ray_line(game, collision_ray, ceil(count * px_per_ray) + i);
		i++;
	}

}
