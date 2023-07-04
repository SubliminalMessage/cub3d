#include <cub3d.h>
// 5 Funciones
int	vars_parse(char* line, t_fileContent *game)
{
	if (!ft_strchr("NSWEFC", line[0]) && line[0] != '\n')
	{
		printf("[x] ERROR CONTENIDO DEL ARCHIVO .cub\n LINE: %s\n",line);
		return (2);
	}
	if (!parse_textures(line,game))
	{
		printf("[x] ERROR TEXTURAS\n LINE: %s\n",line);
		return (2);
	}
	if (!parse_CF(line , game))
	{
		printf("[x] ERROR COLORES DEL TECHO/SUELO\n LINE: %s\n",line);
		return (2);
	}
	if (isTexture(game->texture) && isRGB(game->F) && isRGB(game->C))
	{
		printf("VARIABLES OK\n***START CHECK MAP***\n");
		return (1);
	}
	return (0);
}
static int read_file__(int fd, int v, t_arrayList* lst,char	*str,t_fileContent *game_data)
{
	if (v == 3)
	{
		arr_add(lst,str);
		return (3);
	}
	if (v == 1 && str[0] != '\n')
	{
		arr_add(lst, str);
		return (3);
	}
	if (v == 0)
		return (vars_parse(str,game_data));
	return (2);
}
static int	read_file_(int fd, t_arrayList* lst,t_fileContent *game_data)
{
	char	*str;
	int		v;

	v = 0;
	str = get_next_line(fd);
	while (str)
	{
		v = read_file__(fd,v,lst,str,game_data);
		if (v == 2)
		{
			close(fd);
			free(str);
			return (0);
		}
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	return (1);
}

int	read_file(char* argv,t_arrayList* lst,t_fileContent *game_data)
{
	int	fd;
	int	r;

	fd = open(argv, O_RDONLY);
	r = 1;
	if (fd>0)
	{
		r = read_file_(fd,lst,game_data);
	}
	else
	{
		close(fd);
		return (0);
	}
	close(fd);
	if (lst->size == 0)
		return (0);
	return (r);
}

void	struct_game_init_textures(t_fileContent *game_data)
{
	game_data->texture[0] = NULL;
	game_data->texture[1] = NULL;
	game_data->texture[2] = NULL;
	game_data->texture[3] = NULL;
	game_data->F[0] = -1;
	game_data->F[1] = -1;
	game_data->F[2] = -1;
	game_data->C[0] = -1;
	game_data->C[1] = -1;
	game_data->C[2] = -1;
}

void	game_data_clear(t_fileContent *game_data)
{
	if(game_data->texture[0] != NULL)
		free(game_data->texture[0]);
	if(game_data->texture[1] != NULL)
		free(game_data->texture[1]);
	if(game_data->texture[2] != NULL)
		free(game_data->texture[2]);
	if(game_data->texture[3] != NULL)
		free(game_data->texture[3]);
}
