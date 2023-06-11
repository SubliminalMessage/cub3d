/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:58:26 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/11 14:12:08 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

#define MAX_INT 2147483647
#define MAX_ITERATIONS 100

static void	calculate_collision(t_ray *ray, t_game *game)
{
	int	iteration;
	t_size map;
	t_point	p;

	iteration = 0;
	p = point(game->player.x, game->player.y);
	map = size(game->map_width, game->map_height);
	while (iteration < MAX_ITERATIONS)
	{
		if (ray->x < 0 || ray->x > map.w || ray->y < 0 || ray->y > map.h)
		{
			iteration = MAX_ITERATIONS;
			continue ;
		}
		if (game->map[(int)ray->y][(int)ray->x] == '0')
		{
			ray->x += ray->x_offset;
			ray->y += ray->y_offset;
			iteration++;
			continue ;
		}
		ray->distance = sqrt(pow((ray->x - p.x), 2) + pow((ray->y - p.y), 2));
		return ;
	}
	ray->distance = MAX_INT;
}

static void	setup_horizontal_ray(t_ray *ray, t_game *game)
{
	ray->distance = MAX_INT;
	if (ray->angle == PI || ray->angle == 0)
		return ;
	if (ray->angle > PI) // Looking up
	{
		ray->y_near = ray->y - floor(ray->y);
		ray->x_near = -ray->y_near / tan(ray->angle);
		ray->y -= ray->y_near + 0.0001;
		ray->x += ray->x_near;
		ray->y_offset = -1;
		ray->x_offset = ray->y_offset / tan(ray->angle);
		ray->collision_side = NORTH;
	}
	else if (ray->angle < PI) // Looking down
	{
		ray->y_near = ceil(ray->y) - ray->y;
		ray->x_near = ray->y_near / tan(ray->angle);
		ray->y += ray->y_near;
		ray->x += ray->x_near;
		ray->y_offset = 1;
		ray->x_offset = ray->y_offset / tan(ray->angle);
		ray->collision_side = SOUTH;
	}
	calculate_collision(ray, game);
}

static void	setup_vertical_ray(t_ray *ray, t_game *game)
{
	ray->distance = MAX_INT;
	if (ray->angle == (PI / 2) || ray->angle == (3 * PI) / 2)
		return ;
	if (ray->angle > (PI / 2) && ray->angle < (3 * PI) / 2) // Looking left
	{
		ray->x_near = floor(ray->x) - ray->x;
		ray->y_near = ray->x_near * tan(ray->angle);
		ray->y += ray->y_near;
		ray->x += ray->x_near - 0.0001;
		ray->x_offset = -1;
		ray->y_offset = ray->x_offset * tan(ray->angle);
		ray->collision_side = WEST;
	}
	else if (ray->angle > (PI / 2) || ray->angle < (3 * PI) / 2) // Looking right
	{
		ray->x_near = ceil(ray->x) - ray->x;
		ray->y_near = ray->x_near * -tan(ray->angle);
		ray->y -= ray->y_near;
		ray->x += ray->x_near;
		ray->x_offset = 1;
		ray->y_offset = ray->x_offset * tan(ray->angle);
		ray->collision_side = EAST;
	}
	calculate_collision(ray, game);
}

t_ray min_ray(t_ray a, t_ray b)
{
	if (a.distance < b.distance)
		return (a);
	return (b);
}

t_ray	ray(t_game *game, float angle, char direction)
{
	t_ray ray;

	ray.x = game->player.x;
	ray.y = game->player.y;
	ray.angle = angle;
	ray.distance = -1;
	ray.collision_side = NONE;
	if (direction == DIR_HORIZONTAL)
		setup_horizontal_ray(&ray, game);
	if (direction == DIR_VERTICAL)
		setup_vertical_ray(&ray, game);
	return (ray);
}
