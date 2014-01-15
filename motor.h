#ifndef MOTOR_H
#define	MOTOR_H

#include "position.h"
#include "detection.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum
{
    none,
    slight_left,
    hard_left,
    slight_right,
    hard_right
    
} adjustment;

void delay_cycle();

void motor_adjust_cycle(adjustment adjustment);

void motor_cycle_foward(adjustment adjustment);

/**
 * Moves the mircomouse one space foward and updates the position
 * @param position the current position of the micromouse
 */
void motor_move_foward(pos_t *position);

/**
 * Turns the micromouse to the specified direction and updates the position
 * @param position the current position of the micromouse
 * @param direction the direction that the mircomouse will face
 */
void motor_turn_to_direction(pos_t *position, dir_t direction);


#ifdef __cplusplus
}
#endif

#endif	/* MOTOR_H */