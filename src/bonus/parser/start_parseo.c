/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parseo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:15 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 20:46:16 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	rm_new_line(t_filecontent *game)
{
	t_arraylist	nwmp;
	int			i;

	i = 0;
	arr_init(&nwmp);
	while (i < game->map.size)
	{
		remove_new_line(game->map.items[i]);
		arr_add(&nwmp, game->map.items[i]);
		i++;
	}
	arr_clear(&game->map);
	game->map = nwmp;
}

static void	append_spaces(t_arraylist *nwmp, char *str, int numSpaces)
{
	size_t	new_len;
	char	*new_str;
	size_t	len;

	len = ft_strlen(str);
	new_len = len + numSpaces;
	new_str = malloc(new_len + 1);
	ft_strlcpy(new_str, str, new_len + 1);
	ft_memset(new_str + len, ' ', numSpaces);
	new_str[new_len] = '\0';
	arr_add(nwmp, new_str);
	free(new_str);
	free(str);
}

void	fill_with_spaces(t_filecontent *game)
{
	int			i;
	char		*str;
	t_arraylist	nwmp;

	arr_init(&nwmp);
	i = 0;
	while (i < game->map.size)
	{
		str = ft_strdup(game->map.items[i]);
		if ((game->y - ft_strlen(str)) > 0)
			append_spaces(&nwmp, str, game->y - ft_strlen(str));
		else
		{
			arr_add(&nwmp, str);
			free(str);
		}
		i++;
	}
	arr_clear(&game->map);
	game->map = nwmp;
}
static int	get_x_size(t_filecontent *game_data)
{
	int	i;
	int	max;

	i = -1;
	max = 0;
	while (++i < game_data->map.size)
		if (ft_strlen(game_data->map.items[i]) > max)
			max = ft_strlen(game_data->map.items[i]);
	return (max);
}
static void	get_size_fill(t_filecontent *game)
{
	int	aux;

	game->x = game->map.size;
	rm_new_line(game);
	game->y = get_x_size(game);
	fill_with_spaces(game);
	// El edu es dislexico
	aux = game->x;
	game->x = game->y;
	game->y = aux;
}

static float	player_o(char c)
{
	float	margin;

	margin = 0.0001;
	if (c == 'N')
		return (ONE_DEGREE * (90 * 3) + margin);
	if (c == 'S')
		return (ONE_DEGREE * 90 + margin);
	if (c == 'W')
		return (ONE_DEGREE * (90 * 2) + margin);
	if (c == 'E')
		return (0.0 + margin);
	return (ONE_DEGREE * 90 + margin);
}
static void	set_player_position(t_filecontent *game_data)
{
	int	i;
	int	j;

	i = 0;
	while (i < game_data->map.size)
	{
		j = 0;
		while (j < ft_strlen(game_data->map.items[i]))
		{
			if (ft_strchr("NSWE", game_data->map.items[i][j]))
			{
				game_data->player_x = j + 0.5;
				game_data->player_y = i + 0.5;
				game_data->player_o = player_o(game_data->map.items[i][j]);
				i = game_data->map.size;
				break ;
			}
			j++;
		}
		i++;
	}
}

int	start_parseo(t_filecontent *game_data, char *argv)
{
	struct_game_init_textures(game_data);
	arr_init(&game_data->map);
	if (!exten_checker(argv, "cub"))
	{
		printf("[x] ERROR EXTENSION ERRONEA\n");
		game_data_clear(game_data);
		arr_clear(&game_data->map);
		return (0);
	}
	if (!read_file(argv, &game_data->map, game_data))
	{
		printf("[x] ERROR CONTENIDO DEL ARCHIVO .cub\n");
		game_data_clear(game_data);
		arr_clear(&game_data->map);
		return (0);
	}
	if (map_checker(game_data->map))
	{
		game_data_clear(game_data);
		arr_clear(&game_data->map);
		return (0);
	}
	set_player_position(game_data);
	get_size_fill(game_data);
	return (1);
}
