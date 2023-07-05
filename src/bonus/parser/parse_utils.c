/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:26 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 20:46:27 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

static t_bool	str_equals(char *a, char *b)
{
	int	a_len;

	if (!a || !b)
		return (a == NULL && b == NULL);
	a_len = ft_strlen(a);
	if (a_len != ft_strlen(b))
		return (false);
	return (ft_strncmp(a, b, a_len) == 0);
}
//FT_STRCMP
int	exten_checker(char *filename, char *extension)
{
	char	*dot;

	if (!filename)
		return (1);
	dot = ft_strrchr(filename, '.');
	if (dot != NULL)
	{
		if (str_equals(dot + 1, extension))
		{ // <? Changed
			return (1);
		}
	}
	return (0);
}

void	remove_new_line(char *str)
{
	char	*position;

	position = ft_strchr(str, '\n');
	if (position != NULL)
	{
		ft_memmove(position, position + 1, ft_strlen(position));
	}
}
