#include "position.h"

void position_rotate_right(pos_t *position)
{
    if (position->direction == direction.north)
    {
        position->direction = direction.east;
    }
    else if (position->direction == direction.east)
    {
        position->direction = direction.south; 
    }
    else if (position->direction == direction.south)
    {
        position->direction = direction.west;
    }
    else if (position->direction == direction.west)
    {
        position->direction = direction.north;
    }
}

void position_rotate_left(pos_t *position)
{
    if (position->direction == direction.north)
    {
        position->direction = direction.west;
    }
    else if (position->direction == direction.east)
    {
        position->direction = direction.north; 
    }
    else if (position->direction == direction.south)
    {
        position->direction = direction.east;
    }
    else if (position->direction == direction.west)
    {
        position->direction = direction.south;
    }
}

void position_move_forward(pos_t *position)
{
    if (position->direction == direction.north)
    {
        position->row += 1;
    }
    else if (position->direction == direction.south)
    {
        position->row -= 1;
    }
    else if (position->direction == direction.east)
    {
        position->column += 1;
    }
    else if (position->direction == direction.west)
    {
        position->column -= 1;
    }
}