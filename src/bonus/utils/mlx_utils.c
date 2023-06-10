/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/10 15:21:28 by dangonza         ###   ########.fr       */
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

void	place_pixel_at(t_img *img, t_point point, int color)
{
	char	*dst;
	int	length;
	int	bpp;

	length = img->line_length;
	bpp = img->bits_per_pixel;
	dst = img->addr + ((int)point.y * length + (int)point.x * (bpp / 8));
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
			place_pixel_at(img, point(x, y), color);
			y++;
		}
		x++;
	}
}

void	draw_line(t_img *img,t_point a, t_point b, int color)
{
	int steps;
	float x_increment;
	float y_increment;
	int i;

	steps = max(abs((int)b.x - (int)a.x), abs((int)b.y - (int)a.y));
	x_increment = (b.x - a.x) / steps;
	y_increment = (b.y - a.y) / steps;

	i = 0;
	while (i <= steps)
	{
		place_pixel_at(img, point(a.x, a.y), color);
		a.x += x_increment;
		a.y += y_increment;
		i++;
	}
}
