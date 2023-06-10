/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dangonza <dangonza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 23:28:34 by dangonza          #+#    #+#             */
/*   Updated: 2023/06/10 15:07:58 by dangonza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

t_point point(float x, float y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}
