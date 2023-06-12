/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dutch <dutch@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 11:59:39 by dangonza          #+#    #+#             */
/*   Updated: 2022/02/27 12:16:18 by dutch            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strrchr(const char *s, int c)
{
	size_t	char_index;
	int		last_seen;

	char_index = 0;
	last_seen = -1;
	while (*(s + char_index))
	{
		if ((unsigned char) *(s + char_index) == (unsigned char) c)
			last_seen = char_index;
		char_index++;
	}
	if (c == '\0')
		last_seen = char_index;
	if (last_seen != -1)
		return ((char *)(s + last_seen));
	return (NULL);
}
