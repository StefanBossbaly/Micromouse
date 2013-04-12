#include "nav.h"
#include "queue.h"

int nav_is_pos_in_bounds(struct nav_array *array, pos_t *position)
{
    return (position->column >= 0) && (position->row >= 0) && (position->column < array->width) && (position->row < array->length);
}

int nav_is_in_bounds(struct nav_array *array, int row, int column)
{
    return (row >= 0) && (column >=0) && (row < array->width) && (column < array->length);
}

int nav_size(struct nav_array *array)
{
    return (array->length * array->width);
}

void nav_init(struct nav_array *array)
{
    int i;
    for(i = 0; i < nav_size(array); i++)
    {
        struct nav_cell *cell = &array->cells[i];
        cell->north = 0;
        cell->south = 0;
        cell->east = 0;
        cell->west = 0;
        cell->has_visited = 0;
        cell->flood_num = -1;
    }
}

struct nav_cell *nav_get_cell_pos(struct nav_array *array, pos_t *position)
{
    return nav_get_cell(array, position->row, position->column);
}

struct nav_cell *nav_get_cell(struct nav_array *array, int row, int column)
{
    int index;
    if (! nav_is_in_bounds(array, row, column))
        return 0;
    
    index = (row * array->width) + column;  
    return &array->cells[index];
}

void nav_reset_flood_num(struct nav_array *array)
{
    int i;
    for(i = 0; i < nav_size(array); i++)
    {
        struct nav_cell *cell = &array->cells[i];
        cell->flood_num = -1;
    }
}

int nav_is_flooded(struct nav_cell *cell)
{
    return (cell->flood_num != -1);
}

void nav_flood(struct nav_array *array)
{
    /*Declare our buffer on the stack*/
    nav_queue_cell cells[256];
    nav_queue queue;
    
    struct nav_cell *first;
    
    nav_reset_flood_num(array);
    
    nav_queue_init(&queue, cells, 256);
    
    /*Start at the first cell and queue it*/
    first =  nav_get_cell(array, 0, 0);
    
    /*Add it to the queue*/
    nav_queue_enqueue(&queue, first, 0 , 0, 0);
    
    while(! nav_queue_empty(&queue))
    {
        /*Declare our buffer on the stack*/
        nav_queue_cell current;
        
        /*Dequeue and fill our buffer*/
        nav_queue_dequeue(&queue, &current);
        
        /*Assign n to the flood number*/
        current.cell->flood_num = current.n;
        
        /*North*/
        if (!current.cell->north && nav_is_in_bounds(array, current.row - 1, current.column))
        {
            struct nav_cell *north_cell = nav_get_cell(array, current.row - 1, current.column);
            
            if (!nav_is_flooded(north_cell) && !nav_queue_is_queued(&queue, north_cell))
            {
                nav_queue_enqueue(&queue, north_cell, current.row - 1, current.column, current.n + 1);
            }
        }
        
        /*East*/
        if (!current.cell->east && nav_is_in_bounds(array, current.row, current.column + 1))
        {
            struct nav_cell *east_cell = nav_get_cell(array, current.row, current.column + 1);
            
            if (!nav_is_flooded(east_cell) && !nav_queue_is_queued(&queue, east_cell))
            {
                nav_queue_enqueue(&queue, east_cell, current.row, current.column + 1, current.n + 1);
            }
        }
        
        /*South*/
        if (!current.cell->south && nav_is_in_bounds(array, current.row + 1, current.column))
        {
            struct nav_cell *south_cell = nav_get_cell(array, current.row + 1, current.column);
            
            if (!nav_is_flooded(south_cell) && !nav_queue_is_queued(&queue, south_cell))
            {
                nav_queue_enqueue(&queue, south_cell, current.row + 1, current.column, current.n + 1);
            }
        }
        
        /*West*/
        if (!current.cell->west && nav_is_in_bounds(array, current.row , current.column - 1))
        {
            struct nav_cell *west_cell = nav_get_cell(array, current.row, current.column - 1);
            
            if (!nav_is_flooded(west_cell) && !nav_queue_is_queued(&queue, west_cell))
            {
                nav_queue_enqueue(&queue, west_cell, current.row, current.column - 1, current.n + 1);
            }
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

void nav_update_wall(struct nav_array *array, pos_t *position, facing dir)
{
    struct nav_cell *cell = nav_get_cell_pos(array, position);
    
    /*Convert the scalar to a direction*/
    direction wall_dir = position_convert_to_direction(position, dir);
    
    /*Update our nav cell*/
    nav_update_wall_cell(cell, wall_dir);
    
    /*Update coresponding cell
    TODO put this code somewhere else in its own subroutine*/
    if (wall_dir == north && nav_is_in_bounds(array, position->row - 1, position->column))
    {
        struct nav_cell *north_cell = nav_get_cell(array, position->row - 1, position->column);
        nav_update_wall_cell(north_cell, south);
    }
    else if (wall_dir == east && nav_is_in_bounds(array, position->row, position->column + 1))
    {
        struct nav_cell *east_cell = nav_get_cell(array, position->row, position->column + 1);
        nav_update_wall_cell(east_cell, west);
    }
    else if (wall_dir == south && nav_is_in_bounds(array, position->row + 1, position->column))
    {
        struct nav_cell *south_cell = nav_get_cell(array, position->row + 1, position->column);
        nav_update_wall_cell(south_cell, north);
    }
    else if (wall_dir == west && nav_is_in_bounds(array, position->row, position->column - 1))
    {
        struct nav_cell *west_cell = nav_get_cell(array, position->row, position->column - 1);
        nav_update_wall_cell(west_cell, east);
    } 
}