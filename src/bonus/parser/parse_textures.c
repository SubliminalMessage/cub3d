#include <cub3d.h>

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
				removeNewLine(line);
				game->texture[i] = ft_strtrim(line + 2, " ");
				if (!extenChecker(game->texture[i], "xpm")
					|| !fileExist(game->texture[i]))
					return (0);
				return (1);
			}
			else
			{
				printf("[X] Error parseando las Texturas de: %s\n", c[i]);
				return (0);
			}
		}
	}
	return (1);
}
