/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_parseo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:15 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:37:01 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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
		printf("Error\nInvalid map extension\n");
		game_data_clear(game_data);
		arr_clear(&game_data->map);
		return (0);
	}
	if (!read_file(argv, &game_data->map, game_data))
	{
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
