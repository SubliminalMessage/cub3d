#include <cub3d.h>

void    arr_init(t_arrayList *list)
{
    list->items = (char **)malloc(1 * sizeof(char *));
    list->capacity = 1;
    list->size = 0;
}
void    arr_add(t_arrayList *list, char *item)
{
    char    **newItems;

    list->items[list->size++] = ft_strdup(item);
    if (list->size == list->capacity) {
        list->capacity *= 2;
        newItems = (char **)malloc(list->capacity * sizeof(char *));
        ft_memcpy(newItems, list->items, list->size * sizeof(char *));
        free(list->items);
        list->items = newItems;
    }
}

void    arr_clear(t_arrayList *list)
{
    int i;

    i = 0;
    while (i < list->size)
        free(list->items[i++]);
    free(list->items);
    list->capacity = 0;
    list->size = 0;
}