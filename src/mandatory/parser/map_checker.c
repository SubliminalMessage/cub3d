/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:50 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/06 13:29:21 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	sstrlen(t_arraylist list, int i)
{
	if (list.size - 1 == i)
		return (ft_strlen(list.items[i]));
	else
		return (ft_strlen(list.items[i]) - 1);
}

static int	map_open_errors(int err, int i, int position, t_arraylist *list)
{
	if (err != 0)
	{
		if (err == 1)
			printf("Error\nInvalid map (weird character).\n");
		else if (err == 2)
			printf("Error\nInvalid map.");
		printf("\nLine: '%s'\n", list->items[i]);
	}
	if (position != 1 || list->size - 1 > i)
	{
		printf("Error\nInvalid map\n");
		err = 1;
	}
	return (err);
}

static int	check_simbol(int i, int j, t_arraylist list, int position)
{
	if (!ft_strchr("1 0NSEW", list.items[i][j]))
		return (1);
	if (ft_strchr("NSEW", list.items[i][j]) && position > 1)
		return (1);
	return (0);
}

static int	check_open(int i, int j, int r_size, t_arraylist list)
{
	if (j == 0 || i == 0 || j == r_size - 1 || i == list.size - 1)
		return (2);
	if ((j >= (ft_strlen(list.items[i - 1]) - 1) || list.items[i - 1][j] == ' ')
		|| (j >= (ft_strlen(list.items[i + 1]) - 1) || list.items[i
			+ 1][j] == ' ') || ((list.items[i][j - 1] == ' ')
			|| (list.items[i][j + 1] == ' ')))
	{
		return (2);
	}
	return (0);
}

int	map_checker(t_arraylist list)
{
	int	vars[4];
	int	position;

	position = 0;
	vars[0] = 0;
	vars[3] = 0;
	while (vars[0] < list.size && vars[3] == 0
		&& list.items[vars[0]][0] != '\n')
	{
		vars[2] = sstrlen(list, vars[0]);
		vars[1] = 0;
		while (vars[1] < vars[2] && vars[3] == 0)
		{
			if (ft_strchr("NSEW", list.items[vars[0]][vars[1]]))
				position += 1;
			vars[3] = check_simbol(vars[0], vars[1], list, position);
			if (ft_strchr("0NSEW", list.items[vars[0]][vars[1]]) && !vars[3])
				vars[3] = check_open(vars[0], vars[1], vars[2], list);
			vars[1]++;
		}
		vars[0]++;
	}
	return (map_open_errors(vars[3], vars[0] - 1, position, &list));
}
