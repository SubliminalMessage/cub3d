#include <cub3d.h>
// 4 Funciones
static int	parse_textures_(char* line, t_fileContent *game, char* c, int i)
{
	if ((ft_strncmp(line, c[i],2) == 0) && (ft_strchr(line, ' ') - line > 0))
	{

		if (!game->texture[i])
		{
			removeNewLine(line);
			game->texture[i] = ft_strtrim(line + 2," ");
			if (!extenChecker(game->texture[i],"xpm") || !fileExist(game->texture[i]))
				return (0);
			return (1);
		}
		else
		{
			printf("[X] Error parseando las Texturas de: %s\n", c[i]);
			return (0);
		}
	}
	return (2);
}

int	parse_textures(char* line, t_fileContent *game)
{
	char	*c[4];
	int			i;
	int			r;

	c[0] = "NO";
	c[1] = "SO";
	c[2] = "WE";
	c[3] = "EA";
	i = -1;
	r = 1;
	while (++i < 4)
	{
		r = parse_textures_(line, game, c, i);
		if (r != 2)
			return (r);
	}
	if (r == 2)
		r = 1;
	return (r);
}

int isRGB(int *n)
{
    return ((n[0] >= 0 && n[0] <= 255)
    && (n[1] >= 0 && n[1] <= 255)
    && (n[2] >= 0 && n[2] <= 255));
}

int	isTexture(char **path)
{
	if (path[0] && path[1] && path[2] && path[3])
	if (extenChecker(path[0],"xpm") && extenChecker(path[1],"xpm")
	&& extenChecker(path[2],"xpm") && extenChecker(path[3],"xpm")
	&& fileExist(path[0]) && fileExist(path[1]) && fileExist(path[2])
	&& fileExist(path[3]))
		return (1);

	return (0);
}
