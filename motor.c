#include "motor.h"

void motor_move_foward(pos_t *position)
{
    /*TODO add the code to make the motor work*/
    
    position_move_forward(position);
}

void motor_turn_to_direction(pos_t *position, direction direction)
{
    /*TODO add the code to make the motor work*/
    
    position->direction = direction;
}