#include "position.h"

int position_equal(pos_t *pos1, pos_t *pos2)
{
    return (pos1->row == pos2->row) && (pos1->column == pos2->column) && (pos1->direction == pos2->direction);
}

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

direction position_invert_direciton(direction dir)
{
    if (dir == north)
    {
        return south;
    }
    else if (dir == east)
    {
        return west;
    }
    else if (dir == south)
    {
        return north;
    }
    else
    {
        return east;
    }
}

direction position_right_adj_direciton(direction dir)
{
    if (dir == north)
    {
        return east;
    }
    else if (dir == east)
    {
        return south;
    }
    else if (dir == south)
    {
        return west;
    }
    else
    {
        return north;
    }
}

direction position_left_adj_direciton(direction dir)
{
    if (dir == north)
    {
        return west;
    }
    else if (dir == east)
    {
        return north;
    }
    else if (dir == south)
    {
        return east;
    }
    else
    {
        return south;
    }
}

direction position_convert_to_direction(pos_t *position, facing dir)
{
    if (dir == front)
    {
        return position->direction;
    }
    else if (dir == back)
    {
        return position_invert_direciton(position->direction);
    }
    else if (dir == right)
    {
        position_right_adj_direciton(position->direction);
    }
    else
    {
        position_left_adj_direciton(position->direction);
    }
}