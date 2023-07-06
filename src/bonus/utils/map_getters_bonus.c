/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:58:47 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 23:59:38 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	get_x_size(t_filecontent *game_data)
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

void	get_size_fill(t_filecontent *game)
{
	int	aux;

	game->x = game->map.size;
	rm_new_line(game);
	game->y = get_x_size(game);
	fill_with_spaces(game);
	aux = game->x;
	game->x = game->y;
	game->y = aux;
}

float	player_o(char c)
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
