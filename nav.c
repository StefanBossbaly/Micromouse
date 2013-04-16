#include "nav.h"
#include "queue.h"
#include "motor.h"

int nav_is_pos_in_bounds(struct nav_array *array, pos_t *position)
{
    return (position->column >= 0) && (position->row >= 0) && (position->column < array->columns) && (position->row < array->rows);
}

int nav_is_in_bounds(struct nav_array *array, int row, int column)
{
    return (row >= 0) && (column >=0) && (row < array->rows) && (column < array->columns);
}

int nav_size(struct nav_array *array)
{
    return (array->rows * array->columns);
}

void nav_init(struct nav_array *array)
{
    int i;
    int size = nav_size(array);
    for(i = 0; i < size; i++)
    {
        struct nav_cell *cell = &array->cells[i];
        cell->north = 0;
        cell->south = 0;
        cell->east = 0;
        cell->west = 0;
        cell->has_visited = 0;
        cell->flood_num = -1;
        cell->row = i / array->columns;
        cell->column = i % array->columns;
    }
}

struct nav_cell *nav_get_cell_pos(struct nav_array *array, pos_t *position)
{
    return nav_get_cell(array, position->row, position->column);
}

struct nav_cell *nav_get_cell(struct nav_array *array, int row, int column)
{
    int index;
    /*if (! nav_is_in_bounds(array, row, column))
        return 0;*/
    
    index = (row * array->columns) + column;  
    return &array->cells[index];
}

void nav_reset_flood_num(struct nav_array *array)
{
    int i;
    int size = nav_size(array);
    for(i = 0; i < size; i++)
    {
        struct nav_cell *cell = &array->cells[i];
        cell->flood_num = -1;
    }
}

int nav_is_flooded(struct nav_cell *cell)
{
    return (cell->flood_num != -1);
}

void nav_flood(struct nav_array *array, pos_t *start)
{
    /*Declare our buffer on the stack*/
    nav_queue_cell cells[256];
    nav_queue queue;
    
    struct nav_cell *first;
    
    nav_reset_flood_num(array);
    
    nav_queue_init(&queue, cells, 256);
    
    /*Start at the first cell and queue it*/
    first =  nav_get_cell_pos(array, start);
    
    /*Add it to the queue*/
    nav_queue_enqueue(&queue, first, 0);
    
    while(! nav_queue_empty(&queue))
    {
        /*Declare our buffer on the stack*/
        nav_queue_cell queue_cell;
        
        /*Current cell*/
        struct nav_cell *cell;
        
        /*Dequeue and fill our buffer*/
        nav_queue_dequeue(&queue, &queue_cell);
        
        /*Assign our current cell*/
        cell = queue_cell.cell;
        
        /*Assign n to the flood number*/
        queue_cell.cell->flood_num = queue_cell.n;
        
        /*North*/
        if (!queue_cell.cell->north && nav_is_in_bounds(array, cell->row - 1, cell->column))
        {
            struct nav_cell *north_cell = nav_get_cell(array, cell->row - 1, cell->column);
            
            if (!nav_is_flooded(north_cell) && !nav_queue_is_queued(&queue, north_cell))
            {
                nav_queue_enqueue(&queue, north_cell, queue_cell.n + 1);
            }
        }
        
        /*East*/
        if (!queue_cell.cell->east && nav_is_in_bounds(array, cell->row, cell->column + 1))
        {
            struct nav_cell *east_cell = nav_get_cell(array, cell->row, cell->column + 1);
            
            if (!nav_is_flooded(east_cell) && !nav_queue_is_queued(&queue, east_cell))
            {
                nav_queue_enqueue(&queue, east_cell, queue_cell.n + 1);
            }
        }
        
        /*South*/
        if (!queue_cell.cell->south && nav_is_in_bounds(array, cell->row + 1, cell->column))
        {
            struct nav_cell *south_cell = nav_get_cell(array, cell->row + 1, cell->column);
            
            if (!nav_is_flooded(south_cell) && !nav_queue_is_queued(&queue, south_cell))
            {
                nav_queue_enqueue(&queue, south_cell, queue_cell.n + 1);
            }
        }
        
        /*West*/
        if (!queue_cell.cell->west && nav_is_in_bounds(array, cell->row , cell->column - 1))
        {
            struct nav_cell *west_cell = nav_get_cell(array, cell->row, cell->column - 1);
            
            if (!nav_is_flooded(west_cell) && !nav_queue_is_queued(&queue, west_cell))
            {
                nav_queue_enqueue(&queue, west_cell, queue_cell.n + 1);
            }
        }
    }
}

void nav_drive_to_target(struct nav_array *array, pos_t *start, pos_t *target)
{
    pos_t current;
    
    current.row = start->row;
    current.column = start->column;
    current.direction = start->direction;
    
    while(! position_equal_location(&current, target))
    {
        /*Get the next lowest neighbor*/
        struct nav_cell *next_cell = nav_get_next_neighbor(array, current.row, current.column);
        
        /*Get the direction to the next cell*/
        direction dir = position_get_direction_to(&current, next_cell->row, next_cell->column);
        
        /*Turn to a direction*/
        motor_turn_to_direction(&current, dir);
        
        /*Move forward*/
        motor_move_foward(&current);
    }
}

struct nav_cell *nav_get_next_neighbor(struct nav_array *array, int row, int column)
{
    struct nav_cell *cell = nav_get_cell(array, row, column);
    int target = cell->flood_num - 1;
    
    /*North*/
    if (nav_is_in_bounds(array, row - 1, column))
    {
        struct nav_cell *north = nav_get_cell(array, row - 1, column);
        
        if (north->flood_num == target)
        {
           return north; 
        }
    }
    /*East*/
    if (nav_is_in_bounds(array, row, column + 1))
    {
        struct nav_cell *east = nav_get_cell(array, row, column + 1);
        
        if (east->flood_num == target)
        {
           return east; 
        }
    }
    /*South*/
    if (nav_is_in_bounds(array, row + 1, column))
    {
        struct nav_cell *south = nav_get_cell(array, row + 1, column);
        
        if (south->flood_num == target)
        {
           return south; 
        }
    }
    /*West*/
    if (nav_is_in_bounds(array, row, column - 1))
    {
        struct nav_cell *west = nav_get_cell(array, row, column - 1);
        
        if (west->flood_num == target)
        {
           return west; 
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