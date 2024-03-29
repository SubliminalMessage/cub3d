/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:20 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:40:02 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	vars_parse(char *line, t_filecontent *game)
{
	if (!ft_strchr("NSWEFC", line[0]) && line[0] != '\n')
	{
		printf("Error\nFile content is not correct.\nLine: '%s'\n", line);
		return (2);
	}
	if (!parse_textures(line, game))
	{
		printf("Error\nTexture is not correct.\nLine: '%s'\n", line);
		return (2);
	}
	if (!parse_cf(line, game))
	{
		printf("Error\nRGB value is not corrext.\nLine: '%s'\n", line);
		return (2);
	}
	if (is_texture(game->texture) && is_rgb(game->f) && is_rgb(game->c))
		return (1);
	return (0);
}

static int	read_file_(int fd, t_arraylist *lst, t_filecontent *game_data)
{
	int		v;
	char	*str;

	v = 0;
	str = get_next_line(fd);
	while (str)
	{
		if (v == 3)
			arr_add(lst, str);
		if (v == 1 && str[0] != '\n')
		{
			arr_add(lst, str);
			v = 3;
		}
		if (v == 0)
			v = vars_parse(str, game_data);
		if (v == 2)
		{
			close(fd);
			return (free(str), 0);
		}
		free(str);
		str = get_next_line(fd);
	}
	return (free(str), 1);
}

int	read_file(char *argv, t_arraylist *lst, t_filecontent *game_data)
{
	int	fd;
	int	r;

	fd = open(argv, O_RDONLY);
	r = 1;
	if (fd > 0)
	{
		r = read_file_(fd, lst, game_data);
	}
	else
	{
		printf("Error\nCannot open the file\n");
		close(fd);
		return (0);
	}
	close(fd);
	if (lst->size == 0)
	{
		printf("Error\nMap not found in file\n");
		return (0);
	}
	return (r);
}

void	struct_game_init_textures(t_filecontent *game_data)
{
	game_data->texture[0] = NULL;
	game_data->texture[1] = NULL;
	game_data->texture[2] = NULL;
	game_data->texture[3] = NULL;
	game_data->f[0] = -1;
	game_data->f[1] = -1;
	game_data->f[2] = -1;
	game_data->c[0] = -1;
	game_data->c[1] = -1;
	game_data->c[2] = -1;
}

void	game_data_clear(t_filecontent *game_data)
{
	if (game_data->texture[0] != NULL)
		free(game_data->texture[0]);
	if (game_data->texture[1] != NULL)
		free(game_data->texture[1]);
	if (game_data->texture[2] != NULL)
		free(game_data->texture[2]);
	if (game_data->texture[3] != NULL)
		free(game_data->texture[3]);
}
