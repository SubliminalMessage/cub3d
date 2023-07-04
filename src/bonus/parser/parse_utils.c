#include <cub3d.h>
// 5 Funciones
int	fileExist(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd>0)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static	t_bool str_equals(char *a, char *b)
{
	int a_len;

	if (!a || !b)
		return (a == NULL && b == NULL);
	a_len = ft_strlen(a);
	if (a_len != ft_strlen(b))
		return (false);
	return (ft_strncmp(a, b, a_len) == 0);
}

int	extenChecker(char *filename, char *extension)
{
	char	*dot;

	if (!filename)
		return (1);
	dot = ft_strrchr(filename, '.');
	if (dot != NULL) {
		if (str_equals(dot + 1, extension)) {
			return (1);
		}
	}
	return (0);
}

void    removeNewLine(char *str)
{
	char	*position;

	position = ft_strchr(str, '\n');
	if (position != NULL) {
		ft_memmove(position, position + 1, ft_strlen(position));
	}
}

int	sstrlen(t_arrayList list, int i)
{
	if (list.size-1 == i)
		return ft_strlen(list.items[i]);
	else
		return ft_strlen(list.items[i]) - 1;
}