/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:31 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:23:56 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

static int	con_(t_filecontent *game, int i)
{
	if (!exten_checker(game->texture[i], "xpm")
		|| !file_exist(game->texture[i]))
		return (0);
	return (1);
}

static int	err_(char **c, int i)
{
	printf("Error\nTried to parse textures\nLine: '%s'\n", c[i]);
	return (0);
}

int	parse_textures(char *line, t_filecontent *game)
{
	char	*c[4];
	int		i;

	c[0] = "NO";
	c[1] = "SO";
	c[2] = "WE";
	c[3] = "EA";
	i = -1;
	while (++i < 4)
	{
		if ((ft_strncmp(line, c[i], 2) == 0) && (ft_strchr(line, ' ')
				- line > 0))
		{
			if (!game->texture[i])
			{
				remove_new_line(line);
				game->texture[i] = ft_strtrim(line + 2, " ");
				return (con_(game, i));
			}
			else
				return (err_(c, i));
		}
	}
	return (1);
}
