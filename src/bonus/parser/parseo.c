/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:20 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 20:46:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	vars_parse(char *line, t_filecontent *game)
{
	if (!ft_strchr("NSWEFC", line[0]) && line[0] != '\n')
	{
		printf("[x] ERROR CONTENIDO DEL ARCHIVO .cub\n LINE: %s\n", line);
		return (2);
	}
	if (!parse_textures(line, game))
	{
		printf("[x] ERROR TEXTURAS\n LINE: %s\n", line);
		return (2);
	}
	if (!parse_cf(line, game))
	{
		printf("[x] ERROR COLORES DEL TECHO/SUELO\n LINE: %s\n", line);
		return (2);
	}
	if (is_texture(game->texture) && is_rgb(game->f) && is_rgb(game->c))
	{
		printf("VARIABLES OK\n***START CHECK MAP***\n");
		return (1);
	}
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
		{
			arr_add(lst, str);
		}
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
			free(str);
			return (0);
		}
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (1);
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
		close(fd);
		return (0);
	}
	close(fd);
	if (lst->size == 0)
		return (0);
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
