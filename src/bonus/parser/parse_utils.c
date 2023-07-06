/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:26 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:14:31 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d_bonus.h>

int	is_rgb(int *n)
{
	return ((n[0] >= 0 && n[0] <= 255) && (n[1] >= 0 && n[1] <= 255)
		&& (n[2] >= 0 && n[2] <= 255));
}

int	is_texture(char **path)
{
	if (path[0] && path[1] && path[2] && path[3])
		if (exten_checker(path[0], "xpm") && exten_checker(path[1], "xpm")
			&& exten_checker(path[2], "xpm") && exten_checker(path[3], "xpm")
			&& file_exist(path[0]) && file_exist(path[1]) && file_exist(path[2])
			&& file_exist(path[3]))
			return (1);
	return (0);
}

int	file_exist(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd > 0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
