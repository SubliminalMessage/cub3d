/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:30:22 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/15 16:20:54 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

t_img	new_image(t_game *game, int w, int h)
{
	t_img	img;

	img.img = mlx_new_image(game->mlx, w, h);
	if (img.img == NULL)
	{
		printf("Error creating image\n");
		close_window(game);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.size = size(w, h);
	return (img);
}

t_img	new_texture(t_game *game, char *path, int width, int height)
{
	t_img	img;

	img.img = mlx_xpm_file_to_image(game->mlx, path, &width, &height);
	if (img.img == NULL)
	{
		printf("Error loading texture '%s'\n", path);
		close_window(game);
	}
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.size = size(width, height);
	return (img);
}

void	place_pixel_at(t_img *img, t_point point, int color)
{
	char	*dst;
	int		length;
	int		bpp;

	if (point.x < 0 || point.y < 0)
		return ;
	if (point.x >= img->size.w || point.y >= img->size.h)
		return ;
	length = img->line_length;
	bpp = img->bits_per_pixel;
	dst = img->addr + ((int)point.y * length + (int)point.x * (bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_line(t_img *img, t_point a, t_point b, int color)
{
	int		steps;
	float	x_increment;
	float	y_increment;
	int		i;

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
