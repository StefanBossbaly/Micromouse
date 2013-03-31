#include "wall.h"

int nav_is_pos_in_bounds(struct nav_array *array, pos_t *position)
{
    return (position->column >= 0) && (position->row >= 0) && (position->column < array->width) && (position->row < array->length);
}

int nav_is_in_bounds(struct nav_array *array, int row, int column)
{
    return (row >= 0) && (column >=0) && (row < array->width) && (column < array->length);
}

void nav_init(struct nav_array *array)
{
    int i;
    int size = (array->length * array->width);
    for(i = 0; i < size; i++)
    {
        struct nav_cell *cell = &array->cells[i];
        cell->north = 0;
        cell->south = 0;
        cell->east = 0;
        cell->west = 0;
        cell->flood_num = -1;
    }
}

struct nav_cell *nav_get_cell_pos(struct nav_array *array, pos_t *position)
{
    if (! nav_is_pos_in_bounds(array, position))
        return 0;
    
    int index = (position->column * array->width) + position->row;
    return &array->cells[index];
}

struct nav_cell *nav_get_cell(struct nav_array *array, int row, int column)
{
    if (! nav_is_in_bounds(array, row, column))
        return 0;
    
    int index = (row * array->width) + column;  
    return &array->cells[index];
}

void nav_reset_visited(struct nav_array *array)
{
    int i;
    int size = array->length * array->width;
    for(i = 0; i < size; i++)
    {
        struct nav_cell *cell = &array->cells[i];
        cell->flood_num = -1;
    }
}

inline int nav_has_visited(struct nav_cell *cell)
{
    return (cell->flood_num != 0);
}

void nav_flood(struct nav_array *array)
{
    //Reset the nav array
    nav_reset_visited(array);
    
    //Start at the beginning
    nav_flood_rec(array, 0, 0, 0);
}

void nav_flood_rec(struct nav_array *array, int row, int column, int flood_num)
{
    struct nav_cell *cell =  nav_get_cell(array, row, column);
    
    //North
    
    //East
    
    //South
    
    //West
}