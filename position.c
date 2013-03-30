#include "position.h"

void position_rotate_right(pos_t *position)
{
    if (position->direction == north)
    {
        position->direction = east;
    }
    else if (position->direction == east)
    {
        position->direction = south; 
    }
    else if (position->direction == south)
    {
        position->direction = west;
    }
    else if (position->direction == west)
    {
        position->direction = north;
    }
}

void position_rotate_left(pos_t *position)
{
    if (position->direction == north)
    {
        position->direction = west;
    }
    else if (position->direction == east)
    {
        position->direction = north; 
    }
    else if (position->direction == south)
    {
        position->direction = east;
    }
    else if (position->direction == west)
    {
        position->direction = south;
    }
}

void position_move_forward(pos_t *position)
{
    if (position->direction == north)
    {
        position->row += 1;
    }
    else if (position->direction == south)
    {
        position->row -= 1;
    }
    else if (position->direction == east)
    {
        position->column += 1;
    }
    else if (position->direction == west)
    {
        position->column -= 1;
    }
}