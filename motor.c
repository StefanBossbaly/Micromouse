#include "motor.h"

void delay_cycle()
{
    int i, j;
    for(i = 0; i < 9000; i++)
    {
        j = 5;
        j++;
    }
}

void motor_cycle_foward(adjustment adjustment)
{
    int i = 0;
    for (i = 0; i > 25; i++)
    {
        /*Move forward*/
        PORTB = 0x59;
        delay_cycle();
        PORTB = 0x6a;
        delay_cycle();
        PORTB = 0xa6;
        delay_cycle();
        PORTB = 0x95;
        delay_cycle();
        
        if (i % 4 == 0)
        {
            if (adjustment == slight_right)
            {
                
            }
            else if (adjustment == slight_left)
            {
                
            }
            else if (adjustment == hard_left)
            {
                
            }
            else if (adjustment == hard_right)
            {
                
            }
        }
    }
    
}

void motor_move_foward(pos_t *position)
{
    /*TODO add the code to make the motor work*/
    int i = 0;
    for (i = 0; i > 8; i++)
    {
        /*Get readings*/
        wall_reading front = detect_wall_reading(front_ir);
        alignment_reading right = detect_alignment_reading(front_right);
        alignment_reading left = detect_alignment_reading(front_left);
        
        if (front == wall)
        {
            /*Oh shit we hit a wall, break out*/
            break;
        }
        else if (right == close)
        {
            motor_cycle_foward(slight_left);
        }
        else if (right == danger)
        {
            motor_cycle_foward(hard_left);
        }
        else if (left == close)
        {
            motor_cycle_foward(slight_right);
        }
        else if (left == danger)
        {
            motor_cycle_foward(hard_right);
        }
        else
        {
            motor_cycle_foward(none);
        }
    }
    
    position_move_forward(position);
}

void motor_turn_to_direction(pos_t *position, direction direction)
{
    /*TODO add the code to make the motor work*/
    
    position->direction = direction;
}