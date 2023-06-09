/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/09 23:43:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img	new_image(void *mlx, int w, int h)
{
	t_img	img;

	img.img = mlx_new_image(mlx, w, h);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
	return (img);
}

void	place_pixel_at(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	fill_image(t_img *img, int color, int sz_x, int sz_y)
{
	int	x;
	int	y;

	x = 0;
	while (x < sz_x)
	{
		y = 0;
		while (y < sz_y)
		{
			place_pixel_at(img, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_img *img, float x1, float y1, float x2, float y2, int color)
{
	int steps;
	float x_increment;
	float y_increment;
	int i;

	steps = max(abs((int)x2 - (int)x1), abs((int)y2 - (int)y1));
	x_increment = (x2 - x1) / steps;
	y_increment = (y2 - y1) / steps;

	i = 0;
	while (i <= steps)
	{
		place_pixel_at(img, x1, y1, color);
		x1 += x_increment;
		y1 += y_increment;
		i++;
	}
}
