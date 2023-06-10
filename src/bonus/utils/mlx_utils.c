/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/11 01:17:30 by dangonza         ###   ########.fr       */
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

void	place_pixel_at(t_img *img, t_point point, t_size size, int color)
{
	char	*dst;
	int	length;
	int	bpp;

	if (point.x < 0 || point.y < 0 || point.x >= size.w || point.y >= size.h)
		return ;
	length = img->line_length;
	bpp = img->bits_per_pixel;
	dst = img->addr + ((int)point.y * length + (int)point.x * (bpp / 8));
	*(unsigned int*)dst = color;
}

void	fill_image(t_img *img, int color, t_size img_size)
{
	int	x;
	int	y;

	x = 0;
	while (x < img_size.w)
	{
		y = 0;
		while (y < img_size.h)
		{
			place_pixel_at(img, point(x, y), img_size, color);
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
		place_pixel_at(img, point(a.x, a.y), size(W_WIDTH, W_HEIGHT), color);
		a.x += x_increment;
		a.y += y_increment;
		i++;
	}
}
