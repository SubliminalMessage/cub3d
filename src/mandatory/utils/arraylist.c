/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arraylist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 20:46:06 by dangonza          #+#    #+#             */
/*   Updated: 2023/07/05 20:46:07 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

void	*ft_realloc(void *ptr, size_t newSize)
{
	void	*new_address;

	new_address = NULL;
	new_address = (void *)realloc(ptr, newSize);
	if (new_address == NULL)
		free(ptr);
	return (new_address);
}

void	arr_init(t_arraylist *list)
{
	list->items = (char **)malloc(1 * sizeof(char *));
	list->capacity = 1;
	list->size = 0;
}

void	arr_add(t_arraylist *list, char *item)
{
	char	**new_items;

	list->items[list->size++] = ft_strdup(item);
	if (list->size == list->capacity)
	{
		list->capacity *= 2;
		new_items = (char **)malloc(list->capacity * sizeof(char *));
		ft_memcpy(new_items, list->items, list->size * sizeof(char *));
		free(list->items);
		list->items = new_items;
	}
}

void	arr_clear(t_arraylist *list)
{
	int	i;

	i = 0;
	while (i < list->size)
		free(list->items[i++]);
	free(list->items);
	list->capacity = 0;
	list->size = 0;
}
