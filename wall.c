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
    return (cell->flood_num != -1);
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
    
    cell->flood_num = flood_num;
    
    //North
    if (nav_is_in_bounds(array, row + 1, column))
    {
        struct nav_cell *north = nav_get_cell(array, row + 1, column);
        
        if (!nav_has_visited(north))
        {
            nav_flood_rec(array, row + 1, column, flood_num + 1);
        }
    }
    
    //East
    if (nav_is_in_bounds(array, row, column + 1))
    {
        struct nav_cell *east = nav_get_cell(array, row, column + 1);
        
        if (!nav_has_visited(east))
        {
            nav_flood_rec(array, row, column + 1, flood_num + 1);
        }
    }
    
    //South
    if (nav_is_in_bounds(array, row - 1, column))
    {
        struct nav_cell *south = nav_get_cell(array, row - 1, column);
        
        if (!nav_has_visited(south))
        {
            nav_flood_rec(array, row - 1, column, flood_num + 1);
        }
    }
    
    //West
    if (nav_is_in_bounds(array, row, column - 1))
    {
        struct nav_cell *west = nav_get_cell(array, row, column - 1);
        
        if (!nav_has_visited(west))
        {
            nav_flood_rec(array, row, column - 1, flood_num + 1);
        }
    }
}

void nav_update_wall_cell(struct nav_cell *cell, direction dir)
{
    if (dir == north)
    {
        cell->north = 1;
    }
    else if (dir == east)
    {
        cell->east = 1;
    }
    else if (dir == south)
    {
        cell->south = 1;
    }
    else
    {
        cell->west = 1;
    }   
}

void nav_update_wall(struct nav_array *array, pos_t *position, scalar dir)
{
    struct nav_cell *cell = nav_get_cell_pos(array, position);
    
    //Convert the scalar to a direction
    direction wall_dir = position_convert_to_direction(position, dir);
    
    //Update our nav cell
    nav_update_wall_cell(cell, wall_dir);
    
    //Update coresponding cell
    //TODO put this code somewhere else in its own subroutine
    if (wall_dir == north && nav_is_in_bounds(array, position->row + 1, position->column))
    {
        struct nav_cell *cell = nav_get_cell(array, position->row + 1, position->column);
        nav_update_wall_cell(cell, south);
    }
    else if (wall_dir == east && nav_is_in_bounds(array, position->row, position->column + 1))
    {
        struct nav_cell *cell = nav_get_cell(array, position->row, position->column + 1);
        nav_update_wall_cell(cell, west);
    }
    else if (wall_dir == south && nav_is_in_bounds(array, position->row - 1, position->column))
    {
        struct nav_cell *cell = nav_get_cell(array, position->row - 1, position->column);
        nav_update_wall_cell(cell, north);
    }
    else if (wall_dir == west && nav_is_in_bounds(array, position->row, position->column - 1))
    {
        struct nav_cell *cell = nav_get_cell(array, position->row, position->column - 1);
        nav_update_wall_cell(cell, east);
    } 
}