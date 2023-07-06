/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 23:56:01 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 23:58:25 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

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

int	exten_checker(char *filename, char *extension)
{
	char	*dot;

	if (!filename)
		return (1);
	dot = ft_strrchr(filename, '.');
	if (dot != NULL)
	{
		if (str_equals(dot + 1, extension))
			return (1);
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

void	rm_new_line(t_filecontent *game)
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

void	append_spaces(t_arraylist *nwmp, char *str, int numSpaces)
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
