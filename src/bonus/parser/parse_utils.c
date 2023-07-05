#include <cub3d.h>

int	isRGB(int *n)
{
	return ((n[0] >= 0 && n[0] <= 255) && (n[1] >= 0 && n[1] <= 255)
		&& (n[2] >= 0 && n[2] <= 255));
}
int	isTexture(char **path)
{
	if (path[0] && path[1] && path[2] && path[3])
		if (extenChecker(path[0], "xpm") && extenChecker(path[1], "xpm")
			&& extenChecker(path[2], "xpm") && extenChecker(path[3], "xpm")
			&& fileExist(path[0]) && fileExist(path[1]) && fileExist(path[2])
			&& fileExist(path[3]))
			return (1);
	return (0);
}
int	fileExist(char *path)
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
int	extenChecker(char *filename, char *extension)
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

void	removeNewLine(char *str)
{
	char	*position;

	position = ft_strchr(str, '\n');
	if (position != NULL)
	{
		ft_memmove(position, position + 1, ft_strlen(position));
	}
}
