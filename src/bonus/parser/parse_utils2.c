#include <cub3d.h>
//5 Funciones
static void	rmvNewLine(t_fileContent  *game)
{
	t_arrayList	nwmp;
	int			i;

	i = 0;
	arr_init(&nwmp);
	while (i < game->map.size)
	{
		removeNewLine(game->map.items[i]);
		arr_add(&nwmp, game->map.items[i]);
		i++;
	}
	arr_clear(&game->map);
	game->map = nwmp;
}

static void	appendSpaces(t_arrayList *nwmp, char *str,int numSpaces)
{
	size_t	newLen;
	char	*newStr;
	size_t	len;

	len = ft_strlen(str);
	newLen = len + numSpaces;
	newStr = malloc(newLen + 1);
	ft_strlcpy(newStr, str, newLen + 1);
	ft_memset(newStr + len, ' ', numSpaces);
	newStr[newLen] = '\0';
	arr_add(nwmp, newStr);
	free(newStr);
	free(str);
}

static void	fillWithSpaces(t_fileContent *game)
{
	int			i;
	char		*str;
	t_arrayList	nwmp;

	arr_init(&nwmp);
	i = 0;
	while (i < game->map.size)
	{
		str = ft_strdup(game->map.items[i]);
		if ((game->Y-ft_strlen(str)) > 0)
			appendSpaces(&nwmp,str,game->Y-ft_strlen(str) );
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

static int	getXSize(t_fileContent *game_data)
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

void	getMapSizeAndFill(t_fileContent *game)
{
	int	aux;

	game->X = game->map.size;
	rmvNewLine(game);
	game->Y = getXSize(game);
	fillWithSpaces(game);
	aux = game->X;
	game->X = game->Y;
	game->Y = aux;
}