#include <cub3d.h>

//------------

int	check_comas_dig(char *str)
{
	int	i;
	int	c;

	c = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == ',')
			c++;
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
	}
	return (c);
}
char	*append_char(char *str, char c)
{
	size_t	length;
	char	*newStr;

	length = ft_strlen(str);
	newStr = malloc((length + 2) * sizeof(char));
	ft_strlcpy(newStr, str, length + 1);
	newStr[length] = c;
	newStr[length + 1] = '\0';
	return (newStr);
}

int	set_cf(char *str, t_filecontent *game, int n)
{
	char	*data[2];
	int		i[2];

	i[0] = -1;
	i[1] = 0;
	data[0] = malloc(1);
	data[0][0] = '\0';
	while (str[++i[0]])
	{
		if (str[i[0]] != ',')
		{
			data[1] = append_char(data[0], str[i[0]]);
			free(data[0]);
			data[0] = data[1];
		}
		if (str[i[0]] == ',' || str[i[0] + 1] == '\0')
		{
			if (n == 0)
				game->f[i[1]++] = ft_atoi(data[0]);
			else
				game->c[i[1]++] = ft_atoi(data[0]);
			data[0][0] = '\0';
		}
	}
	free(data[0]);
	return (1);
}

int	parse_cf(char *line, t_filecontent *game)
{
	char	*ax;
	int		r;

	r = 1;
	if (((line[0] == 'F') || (line[0] == 'C')) && (ft_strchr(line, ' ')
			- line > 0))
	{
		remove_new_line(line);
		ax = ft_strtrim(line + 1, " ");
		if (check_comas_dig(ax) != 2)
		{
			free(ax);
			return (0);
		}
		if (line[0] == 'F')
		{
			r = set_cf(ax, game, 0);
			r = is_rgb(game->f);
		}
		else
		{
			set_cf(ax, game, 1);
			r = is_rgb(game->c);
		}
		free(ax);
	}
	return (r);
}
