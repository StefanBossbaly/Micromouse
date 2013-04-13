#ifndef MOTOR_H
#define	MOTOR_H

#include "position.h"

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
void motor_turn_to_direction(pos_t *position, direction direction);



#endif	/* MOTOR_H */