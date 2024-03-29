/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 01:07:06 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:05:46 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

typedef struct s_ray_line
{
	float	v_offset;
	int		color;
	int		box_y;
}			t_ray_line;

void	draw_ray_line(t_game *game, t_ray ray, int screen_x)
{
	t_img		texture;
	t_ray_line	info;
	int			screen_y;
	int			px;

	texture = game->north_texture;
	if (ray.collision_side == SOUTH)
		texture = game->south_texture;
	if (ray.collision_side == EAST)
		texture = game->east_texture;
	if (ray.collision_side == WEST)
		texture = game->west_texture;
	info.v_offset = (ray.real_height - ray.projected_height) / 2;
	px = -1;
	while (++px <= ray.projected_height)
	{
		info.box_y = floor(32 * ((px + info.v_offset) / ray.real_height));
		info.color = get_color_from_image(&texture, (int)ray.box_x, info.box_y);
		screen_y = ((W_HEIGHT / 2) - (ray.projected_height / 2)) + px;
		place_pixel_at(&game->canvas, point(screen_x, screen_y), info.color);
	}
}

typedef struct s_ray_info
{
	float	ray_angle;
	float	correct_distance;
	float	px_per_ray;
	float	img_x;
	int		i;
}			t_ray_info;

float	correct_angle(float angle)
{
	angle -= 0.01;
	if (angle < 0)
		return (angle + PI * 2);
	if (angle > PI * 2)
		return (angle - PI * 2);
	return (angle);
}

/**
 * @note Sides SOUTH and WEST gets inverted
*/
void	save_ray_info(t_ray_info *info, t_game *game, t_ray col_ray)
{
	info->px_per_ray = (float)W_WIDTH / (float)(FOV * FOV_DENSITY);
	info->ray_angle = game->player.angle - col_ray.angle;
	info->correct_distance = col_ray.distance * cos(info->ray_angle);
	info->img_x = 0;
	if (col_ray.collision_side == NORTH || col_ray.collision_side == SOUTH)
		info->img_x = col_ray.x - floor(col_ray.x);
	if (col_ray.collision_side == EAST || col_ray.collision_side == WEST)
		info->img_x = col_ray.y - floor(col_ray.y);
	if (col_ray.collision_side == SOUTH || col_ray.collision_side == WEST)
		info->img_x = 1 - info->img_x;
	info->img_x = floor(info->img_x * 32);
}

void	draw_ray(t_game *game, float angle, int count)
{
	t_ray		collision_ray;
	t_ray_info	ray_info;

	angle = correct_angle(angle);
	collision_ray = min_ray(ray(game, angle, 'H'), ray(game, angle, 'V'));
	save_ray_info(&ray_info, game, collision_ray);
	collision_ray.real_height = (32 * 30) / ray_info.correct_distance;
	collision_ray.projected_height = collision_ray.real_height;
	if (collision_ray.projected_height > W_HEIGHT)
		collision_ray.projected_height = W_HEIGHT;
	collision_ray.box_x = (int)ray_info.img_x;
	ray_info.i = -1;
	while (++(ray_info.i) < ray_info.px_per_ray)
		draw_ray_line(game, collision_ray, ceil(count * ray_info.px_per_ray)
			+ ray_info.i);
}
