#include <cub3d.h>
//UTILS

int sstrlen(t_arrayList list, int i)
{
	if(list.size-1 == i)
		return ft_strlen(list.items[i]);
	else
		return ft_strlen(list.items[i])-1;
}

//THIS FILE
static int	map_open_errors(int err, int i, int j, int position,t_arrayList *list)
{
	if (err != 0)
	{
		if (err == 1)
			printf("[x] ERROR SIMBOLO DUPLICADO/DESCONOCIDO\n");
		else if (err == 2)
			printf("[x] ERROR MAPA\n");
		printf("POSICION: %d , %d\n", i, j);
		printf("LINEA : %s \n", list->items[i]);
		i = 0;
		while (i<list->size)
			printf("%s\n", list->items[i++]);
		printf("\n");
	}
	if(position != 1 || list->size - 1 > i)
	{
		printf("[x] ERROR MAP INVALID\n");
		err = 1;
	}
	return (err);
}

static int check_simbol(int i, int j, t_arrayList list,int position)
{
    if (!ft_strchr("1 0NSEW", list.items[i][j]))
        return (1);
	if(ft_strchr("NSEW", list.items[i][j])
		&& position > 1)
		return (1);
    return (0);
}

static int check_open(int i, int j,int r_size, t_arrayList list)
{
    if(j == 0 || i == 0 || j == r_size - 1 || i == list.size - 1)
		return(2);
	if ((j >= (ft_strlen(list.items[i - 1]) - 1)
		|| list.items[i - 1][j] == ' ')
		|| (j >= (ft_strlen(list.items[i + 1]) - 1)
		|| list.items[i + 1][j] == ' ')
		|| ((list.items[i][j - 1] == ' ')
		|| (list.items[i][j + 1] == ' '))){
		return(2);
		}
    return(0);
}

int	map_checker(t_arrayList list)
{
	//0 == i , 1 == j, 2 == r_size, 3 == err
	int	vars[4];
	int position;

	position = 0;
	vars[0] = 0;
	vars[3] = 0;
	while (vars[0] < list.size && vars[3] == 0 && list.items[vars[0]][0] != '\n')
	{
		vars[2] = sstrlen(list, vars[0]);
		vars[1] = 0;
		while (vars[1] < vars[2] && vars[3] == 0)
		{
			if(ft_strchr("NSEW", list.items[vars[0]][vars[1]]))
				position += 1;
            vars[3] = check_simbol(vars[0],vars[1],list,position);
			if (ft_strchr("0NSEW", list.items[vars[0]][vars[1]]) && !vars[3])
				vars[3] = check_open(vars[0],vars[1],vars[2], list);
			vars[1]++;
		}
		vars[0]++;
	}
	return (map_open_errors(vars[3], vars[0] - 1, vars[1] - 1,position, &list));
}

//RECURSIVI WONDER
int map_checker_recursive(t_arrayList list, int row, int col, int position, int err)
{
	int nextRow;
	int nextCol;

	if (row < 0 || row >= list.size || col < 0 || col >= sstrlen(list, row) || err)
		return map_open_errors(err, row - 1, col - 1, position, &list);
	if (ft_strchr("NSEW", list.items[row][col]))
		position += 1;
	err = check_simbol(row, col, list, position);
	if (ft_strchr("0NSEW", list.items[row][col]) && !err)
		err = check_open(row, col, sstrlen(list, row), list);
	nextRow = row;
	nextCol = col + 1;
	if (nextCol >= sstrlen(list, nextRow)) {
		nextRow += 1;
		nextCol = 0;
	}
	return map_checker_recursive(list, nextRow, nextCol, position, err);
}
int map_checker_r(t_arrayList list)
{
	return map_checker_recursive(list, 0, 0, 0, 0);
}
